// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_POINTER_H_
#define INCLUDE_RAPIDSCHEMA_POINTER_H_

#include <string>
#include <list>

namespace rapidschema {

class Pointer {
 public:
  Pointer() = default;

  explicit Pointer(const std::list<std::string> &path)
      : path_(path) {}

  const void PrependTokenToPointer(const std::string &token) {
    path_.push_front(token);
  }

  const std::list<std::string> &GetPath() const {
    return path_;
  }

 private:
  std::list<std::string> path_;
};

inline bool operator==(const Pointer &lhs, const Pointer &rhs) {
  return lhs.GetPath() == rhs.GetPath();
}

inline bool operator!=(const Pointer &lhs, const Pointer &rhs) {
  return (lhs == rhs) == false;
}

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_POINTER_H_
