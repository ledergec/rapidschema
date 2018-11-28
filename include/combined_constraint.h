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

#include "meta_utils.h"
#include "transform_result.h"

namespace rapidoson {

    template<typename T, template<typename> class ... Constraints>
    class CombinedConstraint;

    template<typename T, template<typename> class ... Constraints>
    static CombinedConstraint<T, Constraints...> MakeConstraint(Constraints<T>&&... constraints);

    template<typename T, template<typename> class ... Constraints>
    class CombinedConstraint {
    public:
        CombinedConstraint() = default;

        TransformResult Check(const T& t) const {
            TransformResult result;
            internal::ForEach(constraints_, [&result, t](const auto &checker) {
                result.Append(checker.Check(t));
            });
            return result;
        }

        template <template<typename> class Constraint>
        Constraint<T>& Get() {
            return internal::TupleAccessor<Constraint<T>, std::tuple<Constraints<T>...>>::Get(constraints_);
        }

    private:
        CombinedConstraint(std::tuple<Constraints<T>...> constraints)
                : constraints_(constraints) {}

    private:
        std::tuple<Constraints<T>...> constraints_;

        friend CombinedConstraint MakeConstraint<T, Constraints...>(Constraints<T>&&... constraints);
    };

    template<typename T, template<typename> class ... Constraints>
    static CombinedConstraint<T, Constraints...> MakeConstraint(Constraints<T>&&... constraints) {
        return CombinedConstraint(std::make_tuple<Constraints<T>...>(
                std::forward<Constraints<T>>(constraints)...));
    }


}  // namespace rapidoson

#endif //RAPIDJSON_COMBINED_CONSTRAINT_H
