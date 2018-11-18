//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef RAPIDJSON_VALUEPARSER_H
#define RAPIDJSON_VALUEPARSER_H

#include "rapidjson/document.h"
#include "transformresult.h"

namespace rapidjson {

    std::string TypeToString(Type type) {
        switch (type) {
            case kArrayType:
                return "array";
            case kFalseType:
                return "false";
            case kTrueType:
                return "true";
            case kObjectType:
                return "object";
            case kNullType:
                return "null";
            case kStringType:
                return "string";
            case kNumberType:
                return "number";
            default:
                assert(false);
        }
    }
}  // rapidjson

#endif //RAPIDJSON_VALUEPARSER_H
