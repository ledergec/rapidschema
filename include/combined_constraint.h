//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef RAPIDJSON_COMBINED_CONSTRAINT_H
#define RAPIDJSON_COMBINED_CONSTRAINT_H

#include <iostream>
#include <optional>
#include <string>
#include <type_traits>

#include <rapidjson/document.h>

#include "transform_result.h"

namespace rapidoson {

    namespace internal {

        template<typename T, std::size_t I, typename... Constraints>
        struct TupleChecker {
            static TransformResult CheckEach(const T& t, const std::tuple<Constraints...>& tuple) {
                TransformResult result;
                result.Append(std::get<I - 1>(tuple).Check(t));
                result.Append(TupleChecker<T, I - 1, Constraints...>::CheckEach(t, tuple));
                return result;
            }
        };

        template<typename T, typename... Constraints>
        struct TupleChecker<T, 0, Constraints...> {
            static TransformResult CheckEach(const T& t, const std::tuple<Constraints...> & tuple) {
                return TransformResult();
            }
        };

        template<typename T, typename Tuple, std::size_t I = 0, class Enabled = void>
        struct TupleAccessor {
            static T& Get(Tuple& tuple) {
                return std::get<I + 1>(tuple);
            }
        };

        template<typename T, typename Tuple, std::size_t I>
        struct TupleAccessor<T, Tuple, I, typename std::enable_if<std::is_same<T, typename std::tuple_element<I, Tuple>::type>::value>::type> {
            static T& Get(Tuple& tuple) {
                return std::get<I>(tuple);
            }
        };

        template<typename T, typename Tuple, std::size_t I>
        struct TupleAccessor<T, Tuple, I, typename std::enable_if<I == std::tuple_size<Tuple>::value>::type> {
        };

    }  // namespace internal

    template<typename T, template<typename> class ... Constraints>
    class CombinedConstraint {
    public:
        CombinedConstraint() = default;

        CombinedConstraint(std::tuple<Constraints<T>...> constraints)
        : constraints_(constraints) {}

        TransformResult Check(const T& t) const {
            return internal::TupleChecker<T, sizeof...(Constraints), Constraints<T>...>::CheckEach(t, constraints_);
        }

        template <template<typename> class Constraint>
        Constraint<T>& Get() {
            return internal::TupleAccessor<Constraint<T>, std::tuple<Constraints<T>...>>::Get(constraints_);
        }

    private:
        std::tuple<Constraints<T>...> constraints_;
    };
}  // namespace rapidoson

#endif //RAPIDJSON_COMBINED_CONSTRAINT_H
