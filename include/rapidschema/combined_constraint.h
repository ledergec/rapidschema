//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef INCLUDE_RAPIDSCHEMA_COMBINED_CONSTRAINT_H_
#define INCLUDE_RAPIDSCHEMA_COMBINED_CONSTRAINT_H_

#include <optional>

#include <rapidjson/document.h>

#include "rapidschema/concepts/correct_value_parameters.h"
#include "rapidschema/meta/unique_tuple.h"
#include "rapidschema/transform_result.h"

namespace rapidschema {

template<typename T, template<typename> class ... Constraints> requires CorrectValueParameters<T, Constraints...>
class CombinedConstraint;

template<typename T, template<typename> class ... Constraints> requires CorrectValueParameters<T, Constraints...>
static CombinedConstraint<T, Constraints...> MakeConstraint(Constraints<T>&&... constraints);

template<typename T, template<typename> class ... Constraints> requires CorrectValueParameters<T, Constraints...>
class CombinedConstraint {
  using TupleT = internal::UniqueTuple<Constraints<T>...>;

 public:
  CombinedConstraint() = default;

  TransformResult Check(const T& t) const {
    TransformResult result;
    constraints_.ForEach([&result, t](const auto &checker) {
      result.Append(checker.Check(t));
    });
    return result;
  }

  template <template<typename> class Constraint>
  Constraint<T>& Get() {
    return constraints_.template GetType<Constraint<T>>();
  }

  template <template<typename> class Constraint>
  const Constraint<T>& Get() const {
    return constraints_.template GetType<Constraint<T>>();
  }

 private:
  explicit CombinedConstraint(TupleT&& constraints)
      : constraints_(std::forward<TupleT>(constraints)) {}

 private:
  TupleT constraints_;

  friend CombinedConstraint MakeConstraint<T, Constraints...>(Constraints<T>&&... constraints);
};

template<typename T, template<typename> class ... Constraints> requires CorrectValueParameters<T, Constraints...>
static CombinedConstraint<T, Constraints...> MakeConstraint(Constraints<T>&&... constraints) {
  return CombinedConstraint(internal::UniqueTuple<Constraints<T>...>(
      std::make_tuple(std::forward<Constraints<T>>(constraints)...)));
}

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_COMBINED_CONSTRAINT_H_
