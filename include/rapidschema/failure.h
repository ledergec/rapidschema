// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_FAILURE_H_
#define INCLUDE_RAPIDSCHEMA_FAILURE_H_

#include <string>
#include <list>

#include "rapidschema/pointer.h"

namespace rapidschema {

struct Failure {
  Failure() = default;

  Failure(const Pointer& pointer, const std::string& mes)
      : pointer_(pointer)
      , message_(mes) {}

  explicit Failure(const std::string& mes)
      : message_(mes) {}

  const Pointer& GetPointer() const {
    return pointer_;
  }

  const void PrependTokenToPointer(const std::string &token) {
    pointer_.PrependTokenToPointer(token);
  }

  const std::string& GetMessage() const {
    return message_;
  }

  Pointer pointer_;
  std::string message_;
};

inline bool operator==(const Failure& lhs, const Failure& rhs) {
  return lhs.GetMessage() == rhs.GetMessage() && lhs.GetPointer() == rhs.GetPointer();
}

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_FAILURE_H_
