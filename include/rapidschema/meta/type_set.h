// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_META_TYPE_SET_H_
#define INCLUDE_RAPIDSCHEMA_META_TYPE_SET_H_

#include <type_traits>

namespace rapidschema {
namespace internal {

template <typename... Ss>
struct TypeSet {
 public:
  template <typename T>
  static constexpr bool Contains();

  static constexpr bool Unique();
};

template <typename S, typename... Ss>
struct TypeSet<S, Ss...> {
 public:
  template <typename T>
  static constexpr bool Contains() {
    return std::is_same<S, T>::value || TypeSet<Ss...>::template Contains<T>();
  }

  static constexpr bool Unique() {
    return !TypeSet<Ss...>::template Contains<S>() && TypeSet<Ss...>::Unique();
  }
};

template <>
struct TypeSet<> {
 public:
  template <typename T>
  static constexpr bool Contains() {
    return false;
  }

  static constexpr bool Unique() {
    return true;
  }
};

}  // namespace internal
}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_META_TYPE_SET_H_
