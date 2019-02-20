// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_SCHEMA_CONSTANT_SCHEMA_IMPL_H_
#define INCLUDE_RAPIDSCHEMA_SCHEMA_CONSTANT_SCHEMA_IMPL_H_

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION

#include "constant_schema.h"

#include "rapidschema/schema/sub_schema.h"

namespace rapidschema {
namespace schema {

template <typename T>
void ConstantSchema<T>::SetConstant(const T& t) {
  const_value = t;
}

template <typename T>
std::shared_ptr<SubSchema> ConstantSchema<T>::CreateSubSchema() const {
  return std::make_shared<SubSchema>(*this);
}

template <typename T>
Object::PropertyMapping ConstantSchema<T>::CreatePropertyMapping() const {
  return {{"const", &const_value}};
}

template class ConstantSchema<bool>;
template class ConstantSchema<int64_t>;
template class ConstantSchema<double>;
template class ConstantSchema<std::string>;

}  // namespace schema
}  // namespace rapidschema

#endif

#endif  // INCLUDE_RAPIDSCHEMA_SCHEMA_CONSTANT_SCHEMA_IMPL_H_
