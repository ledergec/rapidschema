// Copyright (C) 2019 Christian Ledergerber

#ifndef UNITTESTS_RAPIDSCHEMA_TEST_UTILS_H_
#define UNITTESTS_RAPIDSCHEMA_TEST_UTILS_H_

#include <iostream>
#include <string>
#include <type_traits>

#include <fmt/format.h>
#include <fmt/ostream.h>

#include <rapidjson/document.h>

#include "rapidschema/value.h"
#include "rapidschema/generic_writer.h"
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

inline Result ParseConfig(const std::string &json, Config *config) {
    rapidjson::Document document;
    rapidjson::ParseResult result = document.Parse(json.c_str());
    EXPECT_FALSE(result.IsError());
    return config->Transform(document);
}

inline Result ParseJsonLeaf(const std::string &json, Config * config) {
    rapidjson::Document document;
    rapidjson::ParseResult result = document.Parse(json.c_str());
    EXPECT_FALSE(result.IsError());
    EXPECT_TRUE(document.HasMember("leaf"));
    return config->Transform(document["leaf"]);
}

template <typename T>
Result ParseLeaf(const T& t, Config * config) {
    auto leaf_str = CreateLeafString(t);
    rapidjson::Document document;
    rapidjson::ParseResult result = document.Parse(leaf_str.c_str());
    EXPECT_FALSE(result.IsError());
    EXPECT_TRUE(document.HasMember("leaf"));
    return config->Transform(document["leaf"]);
}

template <typename T>
Result ValidateLeaf(const T& t, Config * config) {
    auto result = ParseLeaf(t, config);
    EXPECT_TRUE(result.Success());
    return config->Validate();
}

template <typename ValueType, typename ConfigType>
Result TestLeafType(ConfigType c) {
    Value<ValueType> value;
    return ParseLeaf(c, &value);
}

inline std::string SerializeConfig(const Config& config) {
    rapidjson::StringBuffer buffer;
    GenericWriter<rapidjson::Writer<rapidjson::StringBuffer>> writer(buffer);
    config.Serialize(&writer);
    return buffer.GetString();
}

}  // namespace rapidschema

#endif  // UNITTESTS_RAPIDSCHEMA_TEST_UTILS_H_
