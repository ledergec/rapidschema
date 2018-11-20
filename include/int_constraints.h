//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef RAPIDJSON_STRING_CONSTRAINTS_H
#define RAPIDJSON_STRING_CONSTRAINTS_H

#include <string>

#include <fmt/format.h>

#include "rapidjson/document.h"
#include "transformresult.h"

namespace rapidoson {

    template<typename MinType, MinType Min, class Enabled = void>
    class Minimum;

    template<typename MinType, MinType Min>
    class Minimum<MinType, Min, typename std::enable_if<std::is_arithmetic<MinType>::value>::type> {
    public:
        static TransformResult Check(MinType n) {
            if (n < Min) {
                return TransformResult(
                        false,
                        "",
                        fmt::format("Expected: >= {}. Actual: {}", Min, n));
            }
            return TransformResult::TRUE;
        }
    };

}  // rapidjson

#endif //RAPIDJSON_STRING_CONSTRAINTS_H
