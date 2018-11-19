//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef RAPIDJSON_COMBINED_CONSTRAINT_H
#define RAPIDJSON_COMBINED_CONSTRAINT_H

#include <string>

#include "rapidjson/document.h"
#include "transformresult.h"

namespace rapidoson {

    template<typename T, typename... Constraints>
    class CombinedConstraint {
    public:
        static TransformResult Check(const T& t);
    };

    template<typename T>
    class CombinedConstraint<T> {
    public:
        static TransformResult Check(const T& t) {
            (void) t;
            return TransformResult::TRUE;
        }
    };

    template<typename T, typename Constraint, typename... Constraints>
    class CombinedConstraint<T, Constraint, Constraints...> {
    public:
        static TransformResult Check(const T& t) {
            auto result = Constraint::Check(t);
            if (result.Success() == false) {
                return result;
            }
            return CombinedConstraint<T, Constraints...>::Check(t);
        }
    };
}  // rapidjson

#endif //RAPIDJSON_COMBINED_CONSTRAINT_H
