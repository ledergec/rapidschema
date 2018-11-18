//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef RAPIDJSON_STRING_CONSTRAINTS_H
#define RAPIDJSON_STRING_CONSTRAINTS_H

#include <string>

#include "rapidjson/document.h"
#include "transformresult.h"

namespace rapidjson {

    template<size_t MinLen>
    class MinLength {
    public:
        static TransformResult Check(const std::string& str) {
            if (str.size() < MinLen) {
                return TransformResult(
                        false,
                        "",
                        std::string("std::string \"").append(str).append("\" is shorter than ").append(std::to_string(MinLen)));
            }
            return TransformResult::TRUE;
        }
    };

    template<size_t MaxLen>
    class MaxLength {
    public:
        static TransformResult Check(const std::string& str) {
            if (str.size() > MaxLen) {
                return TransformResult(
                        false,
                        "",
                        std::string("std::string \"").append(str).append("\" exeeds maximum length ").append(std::to_string(MaxLen)));
            }
            return TransformResult::TRUE;
        }
    };

}  // rapidjson

#endif //RAPIDJSON_STRING_CONSTRAINTS_H
