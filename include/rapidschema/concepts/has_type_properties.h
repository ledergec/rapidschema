//
// Created by root on 12/9/18.
//

#include "rapidschema/type_properties.h"

#ifndef INCLUDE_RAPIDSCHEMA_CONCEPTS_HAS_TYPE_PROPERTIES_H_
#define INCLUDE_RAPIDSCHEMA_CONCEPTS_HAS_TYPE_PROPERTIES_H_

namespace rapidschema {

namespace internal {

template<class T, std::size_t = sizeof(T)>
std::true_type CheckSpecializationExists(T *);

std::false_type CheckSpecializationExists(...);

template<class T>
using SpecializationExists = decltype(CheckSpecializationExists(std::declval<T *>()));

}  // namespace internal

/// \brief Concept checking whether the TypePoperties<T> specialization exists.
template<typename T>
concept bool HasTypeProperties = internal::SpecializationExists<TypeProperties<T>>::value;

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_CONCEPTS_HAS_TYPE_PROPERTIES_H_
