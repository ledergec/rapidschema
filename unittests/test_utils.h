//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef RAPIDJSON_TEST_UTILS_H
#define RAPIDJSON_TEST_UTILS_H

#include <iostream>
#include <string>
#include <type_traits>
#include <variant>

#include <rapidjson/document.h>

#include <fmt/format.h>
#include <fmt/ostream.h>

#include "configvalue.h"
#include "json_type_set.h"

namespace rapidoson {

    static TransformResult ParseObject(const std::string &json, Config *config) {
        rapidjson::Document document;
        rapidjson::ParseResult result = document.Parse(json.c_str());
        assert(result.IsError() == false);
        return config->Parse(document);
    }

    static TransformResult ParseLeaf(const std::string &json, Config *config) {
        rapidjson::Document document;
        rapidjson::ParseResult result = document.Parse(json.c_str());
        assert(result.IsError() == false);
        assert(document.HasMember("leaf"));
        return config->Parse(document["leaf"]);
    }

    template<typename ConfigType, class Enable = void>
    struct ToJsonValue {
        static std::string Convert(const ConfigType& c);
    };

    template <>
    struct ToJsonValue<std::string, std::enable_if<std::true_type::value>::type> {
        static std::string Convert(const std::string& c) {
            return fmt::format(R"("{}")", c);
        }
    };

    template <>
    struct ToJsonValue<std::nullptr_t, std::enable_if<std::true_type::value>::type> {
        static std::string Convert(const std::nullptr_t& c) {
            return "null";
        }
    };

    template <typename ConfigType>
    struct ToJsonValue<ConfigType, typename std::enable_if<std::is_integral<ConfigType>::value>::type> {
        static std::string Convert(const ConfigType& c) {
            return fmt::format(R"({})", c);
        }
    };

    template <typename ConfigType>
    struct ToJsonValue<ConfigType, typename std::enable_if<std::is_floating_point<ConfigType>::value>::type> {
        static std::string Convert(const ConfigType& c) {
            return fmt::format(R"({:.1f})", c);
        }
    };

    template <typename T, template<typename> class... Constraints>
    TransformResult TestLeafConstraints(const T& t) {
        std::string json = fmt::format(R"(
                {{
                  "leaf": {}
                }}
                )", ToJsonValue<T>::Convert(t));

        ConfigValue<T, Constraints...> value("leaf");
        auto result = ParseLeaf(json, &value);
        EXPECT_TRUE(result.Success());
        return value.Validate();
    }

    template <typename T, template<typename> class... Constraints>
    TransformResult TestValueConstraints(ConfigValue<T, Constraints...>* value, T t) {

        std::string json = fmt::format(R"(
                {{
                  "leaf": {}
                }}
                )", ToJsonValue<T>::Convert(t));

        value->SetName("leaf");
        auto result = ParseLeaf(json, value);
        EXPECT_TRUE(result.Success());
        return value->Validate();
    }

    template <typename ValueType, typename ConfigType>
    TransformResult TestLeafType(ConfigType c) {
        std::string json = fmt::format(R"(
                {{
                  "leaf": {}
                }}
                )", ToJsonValue<ConfigType>::Convert(c));

        ConfigValue<ValueType> value("leaf");
        return ParseLeaf(json, &value);
    }

}  // rapidjson

#endif //RAPIDJSON_TEST_UTILS_H
