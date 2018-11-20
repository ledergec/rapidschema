//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef RAPIDJSON_TYPE_NAME_H
#define RAPIDJSON_TYPE_NAME_H

#include <string>

#include "rapidjson/document.h"

namespace rapidoson {

    template <typename T>
    struct TypeName;

    template <>
    struct TypeName<int8_t> {
        static constexpr char name[] = "int8";
    };

    template <>
    struct TypeName<uint8_t> {
        static constexpr char name[] = "uint8";
    };

    template <>
    struct TypeName<int16_t> {
        static constexpr char name[] = "int16";
    };

    template <>
    struct TypeName<uint16_t> {
        static constexpr char name[] = "uint16";
    };

    template <>
    struct TypeName<int32_t> {
        static constexpr char name[] = "int32";
    };

    template <>
    struct TypeName<uint32_t> {
        static constexpr char name[] = "uint32";
    };

    template <>
    struct TypeName<int64_t> {
        static constexpr char name[] = "int64";
    };

    template <>
    struct TypeName<uint64_t> {
        static constexpr char name[] = "uint64";
    };

    template <>
    struct TypeName<float> {
        static constexpr char name[] = "float";
    };

    template <>
    struct TypeName<double> {
        static constexpr char name[] = "double";
    };

    template <>
    struct TypeName<std::string> {
        static constexpr char name[] = "std::string";
    };

    template <>
    struct TypeName<std::nullptr_t> {
        static constexpr char name[] = "nullptr_t";
    };

}  // rapidjson

#endif //RAPIDJSON_TYPE_NAME_H
