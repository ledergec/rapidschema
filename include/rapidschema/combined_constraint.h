//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef INCLUDE_RAPIDSCHEMA_COMBINED_CONSTRAINT_H_
#define INCLUDE_RAPIDSCHEMA_COMBINED_CONSTRAINT_H_

#include <iostream>
#include <optional>
#include <string>
#include <tuple>
#include <type_traits>

#include <rapidjson/document.h>

#include "rapidschema/meta/meta_utils.h"
#include "rapidschema/transform_result.h"

namespace rapidschema {

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
    return std::get<Constraint<T>>(constraints_);
  }

 private:
  explicit CombinedConstraint(std::tuple<Constraints<T>...> constraints)
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


}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_COMBINED_CONSTRAINT_H_
