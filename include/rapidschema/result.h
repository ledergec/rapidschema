// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_RESULT_H_
#define INCLUDE_RAPIDSCHEMA_RESULT_H_

#include <algorithm>
#include <cassert>
#include <string>
#include <vector>

#include "rapidschema/failure.h"
#include "rapidschema/modern_types/optional.h"

namespace rapidschema {
namespace internal {

class FailureCollection {
 public:
  FailureCollection() {}

  explicit FailureCollection(const Failure& failure) {
    failures_.push_back(failure);
  }

  const std::vector<Failure>& GetFailures() const {
    return failures_;
  }

  void Append(const FailureCollection& other) {
    auto other_vector = other.GetFailures();
    std::copy(other_vector.begin(), other_vector.end(), std::back_inserter(failures_));
  }

  void Append(const Failure& other) {
    failures_.push_back(other);
  }

  void PrependTokenToPointer(const std::string &token) {
    for (auto& failure : failures_) {
      failure.PrependTokenToPointer(token);
    }
  }

 private:
  std::vector<Failure> failures_;
};

static absl::optional<FailureCollection> Append(
    absl::optional<FailureCollection> lhs,
    const absl::optional<FailureCollection>& rhs) {
  if (lhs.has_value()) {
    if (rhs.has_value()) {
      lhs.value().Append(rhs.value());
      return lhs;
    } else {
      return lhs;
    }
  } else {
    return rhs;
  }
}

static absl::optional<FailureCollection> Append(
    absl::optional<FailureCollection> lhs,
    const absl::optional<Failure>& rhs) {
  if (lhs.has_value()) {
    if (rhs.has_value()) {
      lhs.value().Append(rhs.value());
      return lhs;
    } else {
      return lhs;
    }
  } else if (rhs.has_value()) {
    return FailureCollection(rhs.value());
  } else {
    return absl::nullopt;
  }
}

}  // namespace internal

class Result {
 public:
  Result()
      : failure_collection_(absl::nullopt) {}

  explicit Result(Failure failure)
      : failure_collection_(failure) {}

  explicit Result(const absl::optional<internal::FailureCollection>& failures)
      : failure_collection_(failures) {}

  bool Success() const {
    return failure_collection_.has_value() == false;
  }

  const std::vector<Failure> GetFailures() const {
    if (Success()) {
      return std::vector<Failure>();
    } else {
      return failure_collection_.value().GetFailures();
    }
  }

  void Append(const Result& other) {
    failure_collection_ = internal::Append(failure_collection_, other.failure_collection_);
  }

  void Append(const absl::optional<Failure>& failure) {
    failure_collection_ = internal::Append(failure_collection_, failure);
  }

  void PrependTokenToPointer(const std::string &token) {
    if (failure_collection_.has_value()) {
      failure_collection_.value().PrependTokenToPointer(token);
    }
  }

  inline bool HasFailures() {
    return failure_collection_.has_value();
  }

 private:
  absl::optional<internal::FailureCollection> failure_collection_;
};

inline Result FailResult(const std::string& message) {
  return Result(Failure(message));
}

inline bool operator== (const Result& lhs, const Result& rhs) {
  return lhs.GetFailures() == rhs.GetFailures();
}

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_RESULT_H_
