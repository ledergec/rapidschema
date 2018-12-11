//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef INCLUDE_RAPIDSCHEMA_RAPIDJSON_TYPE_TO_STRING_H_
#define INCLUDE_RAPIDSCHEMA_RAPIDJSON_TYPE_TO_STRING_H_

#include <string>

#include <rapidjson/document.h>

namespace rapidschema {

inline std::string JsonTypeToString(rapidjson::Type type) {
    switch (type) {
        case rapidjson::kArrayType:
            return "array";
        case rapidjson::kFalseType:
            return "false";
        case rapidjson::kTrueType:
            return "true";
        case rapidjson::kObjectType:
            return "object";
        case rapidjson::kNullType:
            return "null";
        case rapidjson::kStringType:
            return "string";
        case rapidjson::kNumberType:
            return "number";
        default:
            assert(false);
        return "";
    }
}

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_RAPIDJSON_TYPE_TO_STRING_H_
