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
#include "to_json_literal.h"

namespace rapidoson {

    template <typename T>
    std::string CreateLeafString(const T& t) {
        return fmt::format(R"(
                {{
                  "leaf": {}
                }}
                )", ToJsonLiteral<T>::Convert(t));
    }

    static TransformResult ParseObject(const std::string &json, Config * config) {
        rapidjson::Document document;
        rapidjson::ParseResult result = document.Parse(json.c_str());
        EXPECT_FALSE(result.IsError());
        return config->Parse(document);
    }

    template <typename T>
    static TransformResult ParseLeaf(const T& t, Config * config) {
        auto leaf_str = CreateLeafString(t);
        rapidjson::Document document;
        rapidjson::ParseResult result = document.Parse(leaf_str.c_str());
        EXPECT_FALSE(result.IsError());
        EXPECT_TRUE(document.HasMember("leaf"));
        return config->Parse(document["leaf"]);
    }

    template <typename T>
    static TransformResult ValidateLeaf(const T& t, Config * config) {
        auto result = ParseLeaf(t, config);
        EXPECT_TRUE(result.Success());
        return config->Validate();
    }

    template <typename ValueType, typename ConfigType>
    TransformResult TestLeafType(ConfigType c) {
        ConfigValue<ValueType> value("leaf");
        return ParseLeaf(c, &value);
    }

}  // rapidjson

#endif //RAPIDJSON_TEST_UTILS_H
