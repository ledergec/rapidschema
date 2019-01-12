// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_CONCEPTS_UNIQUE_TYPES_H_
#define INCLUDE_RAPIDSCHEMA_CONCEPTS_UNIQUE_TYPES_H_

#ifdef RAPIDSCHEMA_WITH_CONCEPTS

#include "rapidschema/meta/type_set.h"

namespace rapidschema {

/// \brief Concept checking whether the all the types in the pack are unique.
template<typename ... T>
concept bool UniqueTypes = internal::TypeSet<T...>::Unique();

}  // namespace rapidschema

#endif

#endif  // INCLUDE_RAPIDSCHEMA_CONCEPTS_UNIQUE_TYPES_H_
