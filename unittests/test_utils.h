//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef RAPIDJSON_TEST_UTILS_H
#define RAPIDJSON_TEST_UTILS_H

#include <string>
#include <variant>
#include <iostream>
#include <type_traits>

#include <rapidjson/document.h>

#include <fmt/format.h>
#include <fmt/ostream.h>

#include "json_type_set.h"
#include "configvalue.h"

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

    template <typename T, typename... Constraints>
    void TestLeafConstraints(const T& t, bool expect_success = true, const std::string &expected_message = "") {
        std::string json = fmt::format(R"(
                {{
                  "leaf": {}
                }}
                )", ToJsonValue<T>::Convert(t));

        ConfigValue<T, Constraints...> value("leaf");
        auto result = ParseLeaf(json, &value);
        if (result.Success() == false) {
            std::cout << "Failed parsing the following json string:" << std::endl <<
            json << std::endl;
        }
        ASSERT_TRUE(result.Success());
        result = value.Validate();
        if (result.Success() == false) {
            std::cout << result.GetMessage() << std::endl;
        }
        ASSERT_EQ(expect_success, result.Success());
        ASSERT_EQ(expected_message, result.GetMessage());
    }

    template <typename T, typename... Constraints>
    void TestValueConstraints(ConfigValue<T, Constraints...>* value,
            T t,
            bool expect_success = true,
            const std::string &expected_message = "") {

        std::string json = fmt::format(R"(
                {{
                  "leaf": {}
                }}
                )", ToJsonValue<T>::Convert(t));

        value->SetName("leaf");
        auto result = ParseLeaf(json, value);
        if (result.Success() == false) {
            std::cout << "Failed parsing the following json string:" << std::endl <<
                      json << std::endl;
        }
        ASSERT_TRUE(result.Success());
        result = value->Validate();
        if (result.Success() == false) {
            std::cout << result.GetMessage() << std::endl;
        }
        ASSERT_EQ(expect_success, result.Success());
        ASSERT_EQ(expected_message, result.GetMessage());
    }

    template <typename ValueType, typename ConfigType>
    void TestLeafType(ConfigType c, bool expect_success = true, const std::string & expected_message = "") {
        std::string json = fmt::format(R"(
                {{
                  "leaf": {}
                }}
                )", ToJsonValue<ConfigType>::Convert(c));

        ConfigValue<ValueType> value("leaf");
        auto result = ParseLeaf(json, &value);
        ASSERT_EQ(expect_success, result.Success());
        ASSERT_EQ(expected_message, result.GetMessage());
    }

}  // rapidjson

#endif //RAPIDJSON_TEST_UTILS_H
