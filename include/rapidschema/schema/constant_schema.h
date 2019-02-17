// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_SCHEMA_CONSTANT_SCHEMA_H_
#define INCLUDE_RAPIDSCHEMA_SCHEMA_CONSTANT_SCHEMA_H_

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION

#include "rapidschema/no_additional_properties.h"
#include "rapidschema/object.h"
#include "rapidschema/value.h"

namespace rapidschema {
namespace schema {

template <typename T>
class ConstantSchema : public NoAdditionalProperties<Object> {
 public:
  Value<T> const_value;

 protected:
  PropertyMapping CreatePropertyMapping() const override {
    return {{"const", &const_value}};
  }
};

using ConstantIntegerSchema = ConstantSchema<int64_t>;
using ConstantNumberSchema = ConstantSchema<double>;
using ConstantStringSchema = ConstantSchema<std::string>;

}  // namespace schema
}  // namespace rapidschema

#endif

#endif  // INCLUDE_RAPIDSCHEMA_SCHEMA_CONSTANT_SCHEMA_H_
