//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef UNITTESTS_RAPIDSCHEMA_TEST_UTILS_H_
#define UNITTESTS_RAPIDSCHEMA_TEST_UTILS_H_

#include <iostream>
#include <string>
#include <type_traits>
#include <variant>

#include <fmt/format.h>
#include <fmt/ostream.h>

#include <rapidjson/document.h>

#include "rapidschema/configvalue.h"
#include "rapidschema/meta/json_type_set.h"
#include "rapidschema/to_json_literal.h"

namespace rapidschema {

template <typename T>
std::string CreateLeafString(const T& t) {
    return fmt::format(R"(
                {{
                  "leaf": {}
                }}
                )", ToJsonLiteral<T>::Convert(t));
}

inline TransformResult ParseObject(const std::string &json, Config * config) {
    rapidjson::Document document;
    rapidjson::ParseResult result = document.Parse(json.c_str());
    EXPECT_FALSE(result.IsError());
    return config->Parse(document);
}

inline TransformResult ParseJsonLeaf(const std::string &json, Config * config) {
    rapidjson::Document document;
    rapidjson::ParseResult result = document.Parse(json.c_str());
    EXPECT_FALSE(result.IsError());
    EXPECT_TRUE(document.HasMember("leaf"));
    return config->Parse(document["leaf"]);
}

template <typename T>
TransformResult ParseLeaf(const T& t, Config * config) {
    auto leaf_str = CreateLeafString(t);
    rapidjson::Document document;
    rapidjson::ParseResult result = document.Parse(leaf_str.c_str());
    EXPECT_FALSE(result.IsError());
    EXPECT_TRUE(document.HasMember("leaf"));
    return config->Parse(document["leaf"]);
}

template <typename T>
TransformResult ValidateLeaf(const T& t, Config * config) {
    auto result = ParseLeaf(t, config);
    EXPECT_TRUE(result.Success());
    return config->Validate();
}

template <typename ValueType, typename ConfigType>
TransformResult TestLeafType(ConfigType c) {
    ConfigValue<ValueType> value("leaf");
    return ParseLeaf(c, &value);
}

}  // namespace rapidschema

#endif  // UNITTESTS_RAPIDSCHEMA_TEST_UTILS_H_
