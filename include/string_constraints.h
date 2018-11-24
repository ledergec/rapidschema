//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef RAPIDJSON_STRING_CONSTRAINTS_H
#define RAPIDJSON_STRING_CONSTRAINTS_H

#include <optional>
#include <string>

#include <fmt/format.h>

#include <rapidjson/document.h>

#include "failure.h"

namespace rapidoson {

    template<size_t MinLen>
    class MinLength {
    public:
        static std::optional<Failure> Check(const std::string& str) {
            if (str.size() < MinLen) {
                return Failure(fmt::format("Expected std::string of length at least {}. Actual: {} of size {}", MinLen, str, str.size()));
            }
            return std::nullopt;
        }
    };

    template<size_t MaxLen>
    class MaxLength {
    public:
        static std::optional<Failure> Check(const std::string& str) {
            if (str.size() > MaxLen) {
                return Failure(fmt::format("Expected std::string of length at most {}. Actual: {} of size {}", MaxLen, str, str.size()));
            }
            return std::nullopt;
        }
    };

}  // rapidjson

#endif //RAPIDJSON_STRING_CONSTRAINTS_H
