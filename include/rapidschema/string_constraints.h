//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef INCLUDE_RAPIDSCHEMA_STRING_CONSTRAINTS_H_
#define INCLUDE_RAPIDSCHEMA_STRING_CONSTRAINTS_H_

#include <optional>
#include <string>

#include <fmt/format.h>

#include <rapidjson/document.h>

#include "rapidschema/failure.h"

namespace rapidschema {

template<typename String = std::string>
class MinLength {
 public:
  MinLength() = default;

  explicit MinLength(size_t min_length)
      : min_length_(min_length) {}

  std::optional<Failure> Check(const String& str) const {
    if (str.size() < min_length_) {
      return Failure(fmt::format("Expected string of length at least {}. Actual: length {} string: \"{}\"",
          min_length_, str.size(), str));
    }
    return std::nullopt;
  }

  void SetMinLength(size_t min_length) {
    min_length_ = min_length;
  }

 private:
  size_t min_length_;
};

template<typename String = std::string>
class MaxLength {
 public:
  MaxLength() = default;

  explicit MaxLength(size_t max_length)
      : max_length_(max_length) {}

  std::optional<Failure> Check(const String& str) const {
    if (str.size() > max_length_) {
      return Failure(fmt::format("Expected string of length at most {}. Actual: length {} string: \"{}\"",
          max_length_, str.size(), str));
    }
    return std::nullopt;
  }

  void SetMaxLength(size_t max_length) {
    max_length_ = max_length;
  }

 private:
  size_t max_length_;
};

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_STRING_CONSTRAINTS_H_
