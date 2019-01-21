// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_MULTIPLE_OF_CONSTRAINT_H_
#define INCLUDE_RAPIDSCHEMA_MULTIPLE_OF_CONSTRAINT_H_

#include <algorithm>
#include <iostream>
#include <string>

#include <fmt/format.h>

#include <rapidjson/document.h>

#include "rapidschema/failure.h"
#include "rapidschema/modern_types/optional.h"

namespace rapidschema {

namespace internal {
template<typename T, class Enabled = void>
class MultipleOf;

template<typename T>
class MultipleOf<T, typename std::enable_if<std::is_integral<T>::value>::type> {
 public:
  MultipleOf()
      : mul_(1) {}

  explicit MultipleOf(const T& mul)
      : mul_(mul) {
    assert(mul_ != 0);
  }

  absl::optional<Failure> Check(const T& n) const {
    if (n % mul_ != 0) {
      return Failure(fmt::format("Expected: MultipleOf {}. Actual: {}", mul_, n));
    }
    return absl::nullopt;
  }

 private:
  T mul_;
};

template<typename T>
class MultipleOf<T, typename std::enable_if<std::is_floating_point<T>::value>::type> {
 public:
  MultipleOf() :
      mul_(1) {}

  explicit MultipleOf(const T& mul)
      : mul_(mul) {
    assert(mul_ != 0);
  }

  absl::optional<Failure> Check(const T& n) const {
    auto lower_diff = n - std::floor(n / mul_) * mul_;
    auto upper_diff = std::ceil(n / mul_) * mul_ - n;
    auto diff = std::min(lower_diff, upper_diff);

    if (diff > 1e-10) {
      auto message = fmt::format("Expected: MultipleOf {}. Actual: {}", mul_, n);
      return Failure(message);
    }
    return absl::nullopt;
  }

 private:
  T mul_;
};
}  // namespace internal

// helper wrapper class which simplifies type inference for compiler
template<typename T>
class MultipleOf {
 public:
  MultipleOf() = default;

  explicit MultipleOf(const T& mul)
      : internal(mul) {}

  absl::optional<Failure> Check(const T& n) const {
    return internal.Check(n);
  }
 private:
  internal::MultipleOf<T> internal;
};

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_MULTIPLE_OF_CONSTRAINT_H_
