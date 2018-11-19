//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef RAPIDJSON_VALUEPARSER_H
#define RAPIDJSON_VALUEPARSER_H

#include <string>

#include "rapidjson/document.h"

namespace rapidoson {

    std::string TypeToString(rapidjson::Type type) {
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
        }
    }

}  // rapidjson

#endif //RAPIDJSON_VALUEPARSER_H
