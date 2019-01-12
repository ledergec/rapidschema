// Copyright (C) 2019 Christian Ledergerber


#ifndef INCLUDE_RAPIDSCHEMA_CONCEPTS_CONSTRAINT_H_
#define INCLUDE_RAPIDSCHEMA_CONCEPTS_CONSTRAINT_H_

#ifdef RAPIDSCHEMA_WITH_CONCEPTS

#include <optional>

#include "rapidschema/failure.h"
#include "rapidschema/transform_result.h"

namespace rapidschema {
namespace internal {

template<typename T, template<typename> class C>
struct IsConstraint {
  template<typename U, std::optional<Failure> (U::*)(const T &) const>
  struct SFINAE {};
  template<typename U>
  static char Test(SFINAE<U, &U::Check> *);
  template<typename U>
  static int Test(...);
  static const bool value = sizeof(Test<C<T>>(nullptr)) == sizeof(char);
};

template<typename T, template<typename> class ... Constraints>
class AreConstraints;

template<typename T, template<typename> class C1,
    template<typename> class ... Constraints>
class AreConstraints<T, C1, Constraints...> {
 public:
  static constexpr bool value = IsConstraint<T, C1>::value && AreConstraints<T, Constraints...>::value;
};

template<typename T>
class AreConstraints<T> {
 public:
  static constexpr bool value = true;
};

}  // namespace internal

/// \brief Concept checking whether all the constraints have a method with the following signature:
/// std::optional<Failure> Check(const T&) const.
template<typename T, template<typename> class ... Constraints>
concept bool AreConstraints = internal::AreConstraints<T, Constraints...>::value;

}  // namespace rapidschema

#endif

#endif  // INCLUDE_RAPIDSCHEMA_CONCEPTS_CONSTRAINT_H_
