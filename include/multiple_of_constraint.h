//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef RAPIDJSON_STRING_CONSTRAINTS_H
#define RAPIDJSON_STRING_CONSTRAINTS_H

#include <optional>
#include <string>

#include <fmt/format.h>

#include "failure.h"
#include "rapidjson/document.h"

namespace rapidoson {

    template<uint32_t Mul, typename T, class Enabled = void>
    class MultipleOf;

    template<uint32_t Mul, typename T>
    class MultipleOf<Mul, T, typename std::enable_if<std::is_integral<T>::value>::type> {
    public:
        std::optional<Failure> Check(const T& n) const {
            if (n % Mul != 0) {
                return std::optional(Failure(fmt::format("Expected: MultipleOf {}. Actual: {}", Mul, n)));
            }
            return std::nullopt;
        }
    };

    template<uint32_t Mul, typename T>
    class MultipleOf<Mul, T, typename std::enable_if<std::is_floating_point<T>::value>::type> {
    public:
        MultipleOf() {}

        std::optional<Failure> Check(const T& n) const {
            auto lower_diff = n - std::floor(n / Mul) * Mul;
            auto upper_diff = std::ceil(n / Mul) * Mul - n;
            auto diff = std::min(lower_diff, upper_diff);

            if (diff > 1e-10) {
                return std::optional(Failure(fmt::format("Expected: MultipleOf {}. Actual: {}", Mul, n)));
            }
            return std::nullopt;
        }
    };

}  // rapidjson

#endif //RAPIDJSON_STRING_CONSTRAINTS_H
