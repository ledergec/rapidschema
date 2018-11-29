//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef RAPIDJSON_VARIANT_H
#define RAPIDJSON_VARIANT_H

#include <assert.h>
#include <optional>
#include <string>
#include <variant>

#include "configvalue.h"
#include "json_type_set.h"

namespace rapidoson {

    namespace internal {

        template <typename V, typename... Ts>
        struct ParseHelper;

        template <typename V, typename T, typename... Ts>
        struct ParseHelper<V, T, Ts...> {
            static TransformResult ParseType(const rapidjson::Value &document, V *v) {
                ConfigValue<T> value;
                auto res = value.Parse(document);
                if (res.Success()) {
                    *v = value;
                    return TransformResult();
                } else {
                    return ParseHelper<V, Ts...>::ParseType(document, v);
                }
            }
        };

        template <typename V>
        struct ParseHelper<V> {
            static TransformResult ParseType(const rapidjson::Value &document, V *v) {
                (void) document;
                (void) v;
                return TransformResult(Failure(fmt::format("No type in variant matched. Actual type: {}",
                        JsonTypeToString(document.GetType()))));
            }
        };

    }

    template<typename... Ts>
    class Variant;

    template<typename... Ts>
    class Variant<ConfigValue<Ts>...> : public Config {
    public:
        Variant(const std::string& name)
                : Config(name) {}

        static_assert(JsonTypeSet<Ts...>::Unique(), "JsonTypes must be unique");

        TransformResult Parse(const rapidjson::Value& document) override {
            return internal::ParseHelper<std::variant<ConfigValue<Ts>...>, Ts...>::ParseType(document, &data_);
        }

        template <typename T>
        ConfigValue<T>& GetVariant() {
            return std::get<ConfigValue<T>>(data_);
        }

        template <typename T>
        const ConfigValue<T>& GetVariant() const {
            return std::get<ConfigValue<T>>(data_);
        }

        template <typename T>
        bool Is() {
            return std::holds_alternative<ConfigValue<T>>(data_);
        }

        TransformResult Validate() const override {
            return std::visit([](const auto & value) {
                return value.Validate();
            }, data_);
        }

    private:
        std::variant<ConfigValue<Ts>...> data_;
};

}  // rapidoson

#endif //RAPIDJSON_VARIANT_H
