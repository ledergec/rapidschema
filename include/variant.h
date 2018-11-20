//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef RAPIDJSON_VARIANT_H
#define RAPIDJSON_VARIANT_H

#include <string>
#include <variant>

#include "json_type_set.h"
#include "configvalue.h"

namespace rapidoson {

    template<typename... ConfigValues>
    class Variant : public Config {
    public:
        Variant(const std::string& name)
                : Config(name) {}

    protected:
        TransformResult ParseInternal(const rapidjson::Value& document) override;
        TransformResult ValidateInternal() const override;
    };

    namespace internal {

        template <typename V, typename... Ts>
        struct ParseHelper {
            static TransformResult ParseType(const rapidjson::Value& document, V* v);
        };

        template <typename V, typename T, typename... Ts>
        struct ParseHelper<V, T, Ts...> {
            TransformResult ParseType(const rapidjson::Value &document, V *v) {
                ConfigValue<T> value;
                auto res = value.Parse(document);
                if (res.Success()) {
                    *v = value.Get();
                    return TransformResult::TRUE();
                } else {
                    return ParseHelper<V, Ts...>::ParseType(document, v);
                }
            }
        };

        template <typename V>
        struct ParseHelper<V> {
            TransformResult ParseType(const rapidjson::Value &document, V *v) {
                (void) document;
                (void) v;
                return TransformResult(false, "", "No type matched");
            }
        };
    }

    template<typename... Ts>
    class Variant<ConfigValue<Ts>...> : public Config {
    public:
        Variant(const std::string& name)
                : Config(name) {}

    protected:
    static_assert(JsonTypeSet<Ts...>::Unique(), "JsonTypes must be unique");

        TransformResult ParseInternal(const rapidjson::Value& document) override {
            return internal::ParseHelper<std::variant<Ts...>, Ts...>::ParseType(document, &data_);
        }

        template <typename U>
        TransformResult ParseType(const rapidjson::Value& document) {
        }

        TransformResult ValidateInternal() const override;

    private:
        std::variant<Ts...> data_;
};

}  // rapidjson

#endif //RAPIDJSON_VARIANT_H
