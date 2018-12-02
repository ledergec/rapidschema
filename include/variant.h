//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef RAPIDJSON_VARIANT_H
#define RAPIDJSON_VARIANT_H

#include <assert.h>
#include <optional>
#include <string>
#include <tuple>

#include "configvalue.h"
#include "json_type_set.h"

namespace rapidoson {

    namespace internal {

        static const int INVALID_VARIANT_INDEX = -1;

        template <typename Tuple, size_t Index>
        struct ParseHelper {
            static std::pair<int, TransformResult> ParseType(const rapidjson::Value &document, Tuple *tuple) {
                auto res = std::get<Index - 1>(*tuple).Parse(document);
                if (res.Success()) {
                    return {Index -1, TransformResult()};
                } else {
                    return ParseHelper<Tuple, Index - 1>::ParseType(document, tuple);
                }
            }
        };

        template <typename Tuple>
        struct ParseHelper<Tuple, 0> {
            static std::pair<int, TransformResult> ParseType(const rapidjson::Value &document, Tuple *tuple) {
                (void) tuple;
                return {-1, TransformResult(Failure(fmt::format("No type in variant matched. Actual type: {}",
                        JsonTypeToString(document.GetType()))))};
            }
        };

        template <typename Tuple, size_t Index>
        using BasicVariantType = typename std::tuple_element<Index, Tuple>::type::Type;

        template <typename Tuple, typename T, size_t Index, class Enabled = void>
        struct ConfigTypeHelper;

        template <typename Tuple, typename T, size_t I>
        struct ConfigTypeHelper<
                Tuple,
                T,
                I,
                typename std::enable_if<std::is_same<T, BasicVariantType<Tuple, I - 1>>::value>::type> {
            using Type = typename std::tuple_element<I - 1, Tuple>::type;
            static constexpr size_t Index = I - 1;
        };

        template <typename Tuple, typename T, size_t I>
        struct ConfigTypeHelper<
                Tuple,
                T,
                I,
                typename std::enable_if<!std::is_same<T, BasicVariantType<Tuple, I - 1>>::value>::type> {
            using Type = typename ConfigTypeHelper<Tuple, T, I - 1>::Type;
            static constexpr size_t Index = ConfigTypeHelper<Tuple, T, I - 1>::Index;
        };

        template <typename Tuple, typename T>
        struct ConfigTypeHelper<
                Tuple,
                T,
                0> {};

        template <typename Tuple, size_t Index>
        struct ConfigValidateHelper {
            static TransformResult Validate(const Tuple & tuple, int32_t index) {
                if (index == Index - 1) {
                    return std::get<Index - 1>(tuple).Validate();
                } else {
                    return ConfigValidateHelper<Tuple, Index - 1>::Validate(tuple, index);
                }
            }
        };

        template <typename Tuple>
        struct ConfigValidateHelper<Tuple, 0> {
            static TransformResult Validate(const Tuple & tuple, int32_t index) {
                assert(false);
                return TransformResult();
            }
        };
    }

    template<typename... ConfigValues>
    class Variant;

    template<typename... ConfigValues>
    Variant<ConfigValues...> MakeVariant(const std::string& name, ConfigValues&&... config_values);

    template<typename... ConfigValues>
    class Variant : public Config {
    public:
        Variant(const std::string& name)
                : Config(name) {}

        static_assert(JsonTypeSet<typename ConfigValues::Type...>::Unique(), "JsonTypes must be unique");

        TransformResult Parse(const rapidjson::Value& document) override {
            auto result = internal::ParseHelper<std::tuple<ConfigValues...>,
                    sizeof...(ConfigValues)>::ParseType(document, &data_);
            variant_index_ = result.first;
            return result.second;
        }

        template<typename T>
        using ConfigTypeOf = internal::ConfigTypeHelper<std::tuple<ConfigValues...>, T, sizeof...(ConfigValues)>;

        template <typename T>
        const typename ConfigTypeOf<T>::Type & GetVariant() const {
            return std::get<ConfigTypeOf<T>::Index>(data_);
        }

        template <typename T>
        typename ConfigTypeOf<T>::Type & GetVariant() {
            return std::get<ConfigTypeOf<T>::Index>(data_);
        }

        template <typename T>
        bool Is() {
            return ConfigTypeOf<T>::Index == variant_index_;
        }

        TransformResult Validate() const override {
            assert(variant_index_ != internal::INVALID_VARIANT_INDEX);
            return internal::ConfigValidateHelper<std::tuple<ConfigValues...>, sizeof...(ConfigValues)>::Validate(data_, variant_index_);
        }

    private:
        int32_t variant_index_ = internal::INVALID_VARIANT_INDEX;
        // must be a tuple because each config value and its constraints must be stored
        std::tuple<ConfigValues...> data_;

        Variant(const std::string& name, std::tuple<ConfigValues...> && data)
                : Config(name)
                , data_(std::forward<std::tuple<ConfigValues...>>(data)) {}

        friend Variant<ConfigValues...> MakeVariant<ConfigValues...>(const std::string& name, ConfigValues&&... config_values);
    };

    template<typename... ConfigValues>
    Variant<ConfigValues...> MakeVariant(const std::string& name, ConfigValues&&... config_values) {
        return Variant<ConfigValues...>(name, std::make_tuple<ConfigValues...>(std::forward<ConfigValues>(config_values)...));
    }

    template<typename T, template<typename> class ... Constraints>
    ConfigValue<T, Constraints...> MakeVariantValue(Constraints<T>&&... constraints) {
        return MakeValue("", std::forward<Constraints<T>>(constraints)...);
    }

}  // rapidoson

#endif //RAPIDJSON_VARIANT_H
