// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_SCHEMA_CONSTANT_SCHEMA_INTERFACE_H_
#define INCLUDE_RAPIDSCHEMA_SCHEMA_CONSTANT_SCHEMA_INTERFACE_H_

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION

#include "rapidschema/schema/sub_schema_interface.h"

namespace rapidschema {
namespace schema {

template <typename T>
class ConstantSchemaInterface : public SubSchemaInterface {
 public:
  virtual void SetConstant(const T& t) = 0;
};

using ConstantIntegerSchemaInterface = ConstantSchemaInterface<int64_t>;
using ConstantNumberSchemaInterface = ConstantSchemaInterface<double>;
using ConstantStringSchemaInterface = ConstantSchemaInterface<std::string>;

}  // namespace schema
}  // namespace rapidschema

#endif

#endif  // INCLUDE_RAPIDSCHEMA_SCHEMA_CONSTANT_SCHEMA_INTERFACE_H_
