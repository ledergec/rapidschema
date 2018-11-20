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

    template<uint32_t Mul, typename T, class Enabled = void>
    class MultipleOf;

    template<uint32_t Mul, typename T>
    class MultipleOf<Mul, T, typename std::enable_if<std::is_integral<T>::value>::type> {
    public:
        static TransformResult Check(T n) {
            if (n % Mul != 0) {
                return TransformResult(
                        false,
                        "",
                        fmt::format("Expected: MultipleOf {}. Actual: {}", Mul, n));
            }
            return TransformResult::TRUE();
        }
    };

//    template<uint32_t Mul, typename T>
//    class MultipleOf<Mul, T, typename std::enable_if<std::is_floating_point<T>::value>::type> {
//    public:
//        MultipleOf()
//                : eps_(1e-8) {}
//
//        static TransformResult Check(T n) {
//            auto lower_diff = n - std::floor(n / Mul) * Mul;
//            auto upper_diff = std::ceil(n / Mul) * Mul - n;
//            auto diff = std::min(lower_diff, upper_diff);
//
//            if (diff < eps_) {
//                return TransformResult(
//                        false,
//                        "",
//                        fmt::format("Expected: MultipleOf {}. Actual: {}", Mul, n));
//            }
//            return TransformResult::TRUE();
//        }
//
//    private:
//        T eps_;
//    };

    template<typename T, T Min, class Enabled = void>
    class Minimum;

    template<typename T, T Min>
    class Minimum<T, Min, typename std::enable_if<std::is_integral<T>::value>::type> {
    public:
        static TransformResult Check(T n) {
            if (n < Min) {
                return TransformResult(
                        false,
                        "",
                        fmt::format("Expected: >= {}. Actual: {}", Min, n));
            }
            return TransformResult::TRUE();
        }
    };

    template<typename T, T Max, class Enabled = void>
    class Maximum;

    template<typename T, T Max>
    class Maximum<T, Max, typename std::enable_if<std::is_arithmetic<T>::value>::type> {
    public:
        static TransformResult Check(T n) {
            if (n > Max) {
                return TransformResult(
                        false,
                        "",
                        fmt::format("Expected: <= {}. Actual: {}", Max, n));
            }
            return TransformResult::TRUE();
        }
    };
}  // rapidjson

#endif //RAPIDJSON_STRING_CONSTRAINTS_H
