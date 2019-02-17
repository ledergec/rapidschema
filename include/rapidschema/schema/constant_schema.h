// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_SCHEMA_CONSTANT_SCHEMA_H_
#define INCLUDE_RAPIDSCHEMA_SCHEMA_CONSTANT_SCHEMA_H_

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION

#include "rapidschema/schema/constant_schema_interface.h"

namespace rapidschema {
namespace schema {

template <typename T>
class ConstantSchema : public NoAdditionalProperties<Object> ,
                       public ConstantSchemaInterface<T> {
 public:
  Value<T> const_value;

  void SetConstant(const T& t);

  std::shared_ptr<SubSchema> CreateSubSchema() const override;

 protected:
  PropertyMapping CreatePropertyMapping() const override;
};

using ConstantIntegerSchema = ConstantSchema<int64_t>;
using ConstantNumberSchema = ConstantSchema<double>;
using ConstantStringSchema = ConstantSchema<std::string>;

}  // namespace schema
}  // namespace rapidschema

#endif

#endif  // INCLUDE_RAPIDSCHEMA_SCHEMA_CONSTANT_SCHEMA_H_
