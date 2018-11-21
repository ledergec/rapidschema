//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef RAPIDJSON_COMBINED_CONSTRAINT_H
#define RAPIDJSON_COMBINED_CONSTRAINT_H

#include <string>
#include <type_traits>
#include <iostream>

#include "rapidjson/document.h"
#include "transformresult.h"

namespace rapidoson {

    namespace internal {

        template<typename T, std::size_t I, typename... Constraints>
        struct TupleChecker {
            static TransformResult CheckEach(const T& t, const std::tuple<Constraints...>& tuple) {
                std::cout << "Checking constraint: " << I << std::endl;
                auto result = std::get<I>(tuple).Check(t);
                if (result.Success() == false) {
                    return result;
                }
                return TupleChecker<T, I + 1, Constraints...>::CheckEach(t, tuple);
            }
        };

        template<typename T, typename... Constraints>
        struct TupleChecker<T, sizeof...(Constraints), Constraints...> {
            static TransformResult CheckEach(const T&, const std::tuple<Constraints...> &) {
                return TransformResult::TRUE();
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

    template<typename T, typename... Constraints>
    class CombinedConstraint {
    public:
        TransformResult Check(const T& t) const {
            return internal::TupleChecker<T, 0, Constraints...>::CheckEach(t, constraints_);
        }

        template <typename Constraint>
        Constraint& Get() {
            return internal::TupleAccessor<Constraint, std::tuple<Constraints...>>::Get(constraints_);
        }

    private:
        std::tuple<Constraints...> constraints_;
    };
}  // namespace rapidoson

#endif //RAPIDJSON_COMBINED_CONSTRAINT_H
