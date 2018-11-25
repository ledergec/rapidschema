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

    template<typename String = std::string>
    class MinLength {
    public:
        MinLength() = default;

        MinLength(size_t min_length)
        : min_length_(min_length) {}

        std::optional<Failure> Check(const std::string& str) {
            if (str.size() < min_length_) {
                return Failure(fmt::format("Expected std::string of length at least {}. Actual: {} of size {}", min_length_, str, str.size()));
            }
            return std::nullopt;
        }

    private:
        size_t min_length_;
    };

    template<typename String = std::string>
    class MaxLength {
    public:
        MaxLength() = default;

        MaxLength(size_t max_length)
        : max_length_(max_length) {}

        std::optional<Failure> Check(const std::string& str) {
            if (str.size() > max_length_) {
                return Failure(fmt::format("Expected std::string of length at most {}. Actual: {} of size {}", max_length_, str, str.size()));
            }
            return std::nullopt;
        }

    private:
        size_t max_length_;
    };

}  // rapidjson

#endif //RAPIDJSON_STRING_CONSTRAINTS_H
