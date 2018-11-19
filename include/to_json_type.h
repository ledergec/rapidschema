//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef RAPIDJSON_TO_JSON_TYPE_H
#define RAPIDJSON_TO_JSON_TYPE_H

#include <string>
#include <type_traits>

#include "json_type.h"

namespace rapidoson {

    template <typename T>
    struct ToJsonType;

    template <>
    struct ToJsonType<std::string> {
        static constexpr JsonType value = JsonType::STRING;
    };

    template <>
    struct ToJsonType<int> {
        static constexpr JsonType value = JsonType::NUMBER;
    };

    template <>
    struct ToJsonType<float> {
        static constexpr JsonType value = JsonType::NUMBER;
    };

    template <>
    struct ToJsonType<double> {
        static constexpr JsonType value = JsonType::NUMBER;
    };

    template <>
    struct ToJsonType<int64_t > {
        static constexpr JsonType value = JsonType::NUMBER;
    };

    template <>
    struct ToJsonType<bool> {
        static constexpr JsonType value = JsonType::BOOLEAN;
    };

    template <>
    struct ToJsonType<std::nullptr_t> {
        static constexpr JsonType value = JsonType::NULLTYPE;
    };

}  // rapidjson

#endif //RAPIDJSON_TO_JSON_TYPE_H
