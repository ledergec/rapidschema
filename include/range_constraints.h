//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef RAPIDJSON_RANGE_CONSTRAINTS_H
#define RAPIDJSON_RANGE_CONSTRAINTS_H

#include <optional>
#include <string>

#include <fmt/format.h>

#include "rapidjson/document.h"
#include "failure_collection.h"

namespace rapidoson {

    template<typename T, T Min, class Enabled = void>
    class Minimum;

    template<typename T, T Min>
    class Minimum<T, Min, typename std::enable_if<std::is_integral<T>::value>::type> {
    public:
        std::optional<Failure> Check(const T& n) const {
            if (n < Min) {
                return Failure(fmt::format("Expected: >= {}. Actual: {}", Min, n));
            }
            return std::nullopt;
        }
    };

    template<typename T, T Min, class Enabled = void>
    class ExclusiveMinimum;

    template<typename T, T Min>
    class ExclusiveMinimum<T, Min, typename std::enable_if<std::is_integral<T>::value>::type> {
    public:
        std::optional<Failure> Check(const T& n) const {
            if (n <= Min) {
                return Failure(fmt::format("Expected: > {}. Actual: {}", Min, n));
            }
            return std::nullopt;
        }
    };

    template<typename T, T Max, class Enabled = void>
    class Maximum;

    template<typename T, T Max>
    class Maximum<T, Max, typename std::enable_if<std::is_arithmetic<T>::value>::type> {
    public:
        std::optional<Failure> Check(const T& n) const {
            if (n > Max) {
                return Failure(fmt::format("Expected: <= {}. Actual: {}", Max, n));
            }
            return std::nullopt;
        }
    };

    template<typename T, T Max, class Enabled = void>
    class ExclusiveMaximum;

    template<typename T, T Max>
    class ExclusiveMaximum<T, Max, typename std::enable_if<std::is_arithmetic<T>::value>::type> {
    public:
        std::optional<Failure> Check(const T& n) const {
            if (n >= Max) {
                return Failure(fmt::format("Expected: < {}. Actual: {}", Max, n));
            }
            return std::nullopt;
        }
    };}  // rapidjson

#endif //RAPIDJSON_RANGE_CONSTRAINTS_H
