//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef RAPIDJSON_RANGE_CONSTRAINTS_H
#define RAPIDJSON_RANGE_CONSTRAINTS_H

#include <optional>
#include <string>

#include <fmt/format.h>

#include "rapidjson/document.h"
#include "transform_result.h"

namespace rapidoson {

    template<typename T>
    class Minimum {
    public:
        Minimum() = default;

        Minimum(const T& min)
        : min_(min) {}

        std::optional<Failure> Check(const T& n) const {
            if (n < min_) {
                return Failure(fmt::format("Expected: >= {}. Actual: {}", min_, n));
            }
            return std::nullopt;
        }

        void SetMin(const T& min) {
            min_ = min;
        }

    private:
        T min_;
    };

    template<typename T>
    class ExclusiveMinimum {
    public:
        ExclusiveMinimum() = default;

        ExclusiveMinimum(const T& min)
                : min_(min) {}

        std::optional<Failure> Check(const T& n) const {
            if (n <= min_) {
                return Failure(fmt::format("Expected: > {}. Actual: {}", min_, n));
            }
            return std::nullopt;
        }

        void SetMin(const T& min) {
            min_ = min;
        }

    private:
        T min_;
    };

    template<typename T>
    class Maximum {
    public:
        Maximum() = default;

        Maximum(const T& max)
        : max_(max) {}

        std::optional<Failure> Check(const T& n) const {
            if (n > max_) {
                return Failure(fmt::format("Expected: <= {}. Actual: {}", max_, n));
            }
            return std::nullopt;
        }

        void SetMax(const T& max) {
            max_ = max;
        }

    private:
        T max_;
    };

    template<typename T>
    class ExclusiveMaximum {
    public:
        ExclusiveMaximum() = default;

        ExclusiveMaximum(const T& max)
                : max_(max) {}

        std::optional<Failure> Check(const T& n) const {
            if (n >= max_) {
                return Failure(fmt::format("Expected: < {}. Actual: {}", max_, n));
            }
            return std::nullopt;
        }

        void SetMax(const T& max) {
            max_ = max;
        }

    private:
        T max_;
    };

}  // rapidjson

#endif //RAPIDJSON_RANGE_CONSTRAINTS_H
