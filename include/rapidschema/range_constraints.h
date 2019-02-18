// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_RANGE_CONSTRAINTS_H_
#define INCLUDE_RAPIDSCHEMA_RANGE_CONSTRAINTS_H_

#include <string>

#include <fmt/format.h>

#include <rapidjson/document.h>

#include "rapidschema/modern_types/optional.h"
#include "rapidschema/result.h"

namespace rapidschema {

template<typename T>
class Minimum {
 public:
  Minimum() = default;

  explicit Minimum(const T& min)
      : min_(min) {}

  absl::optional<Failure> Check(const T& n) const {
    if (n < min_) {
      return Failure(fmt::format("Expected: >= {}. Actual: {}", min_, n));
    }
    return absl::nullopt;
  }

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION
  template <typename SchemaType>
  void AddToSchema(std::shared_ptr<SchemaType> schema) const {
    schema->SetMinimum(min_);
  }
#endif

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

  explicit ExclusiveMinimum(const T& min)
      : min_(min) {}

  absl::optional<Failure> Check(const T& n) const {
    if (n <= min_) {
      return Failure(fmt::format("Expected: > {}. Actual: {}", min_, n));
    }
    return absl::nullopt;
  }

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION
  template <typename SchemaType>
  void AddToSchema(std::shared_ptr<SchemaType> schema) const {
    schema->SetExclusiveMinimum(min_);
  }
#endif

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

  explicit Maximum(const T& max)
      : max_(max) {}

  absl::optional<Failure> Check(const T& n) const {
    if (n > max_) {
      return Failure(fmt::format("Expected: <= {}. Actual: {}", max_, n));
    }
    return absl::nullopt;
  }

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION
  template <typename SchemaType>
  void AddToSchema(std::shared_ptr<SchemaType> schema) const {
    schema->SetMaximum(max_);
  }
#endif

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

  explicit ExclusiveMaximum(const T& max)
      : max_(max) {}

  absl::optional<Failure> Check(const T& n) const {
    if (n >= max_) {
      return Failure(fmt::format("Expected: < {}. Actual: {}", max_, n));
    }
    return absl::nullopt;
  }

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION
  template <typename SchemaType>
  void AddToSchema(std::shared_ptr<SchemaType> schema) const {
    schema->SetExclusiveMaximum(max_);
  }
#endif

  void SetMax(const T& max) {
    max_ = max;
  }

 private:
  T max_;
};

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_RANGE_CONSTRAINTS_H_
