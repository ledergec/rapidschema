// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_META_JSON_TYPE_SET_H_
#define INCLUDE_RAPIDSCHEMA_META_JSON_TYPE_SET_H_

#include "rapidschema/type_properties.h"

namespace rapidschema {
namespace internal {

template<typename... Ss>
struct JsonTypeSet {
 public:
  template<typename T>
  static constexpr bool Contains();

  static constexpr bool Unique();
};

template<typename S, typename... Ss>
struct JsonTypeSet<S, Ss...> {
 public:
  template<typename T>
  static constexpr bool Contains() {
    return TypeProperties<T>::GetJsonType() == TypeProperties<S>::GetJsonType() ||
        JsonTypeSet<Ss...>::template Contains<T>();
  }

  static constexpr bool Unique() {
    return !JsonTypeSet<Ss...>::template Contains<S>() && JsonTypeSet<Ss...>::Unique();
  }
};

template<>
struct JsonTypeSet<> {
 public:
  template<typename T>
  static constexpr bool Contains() {
    return false;
  }

  static constexpr bool Unique() {
    return true;
  }
};

}  // namespace internal
}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_META_JSON_TYPE_SET_H_
