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

  void SetConstant(const T& t) override;

  std::shared_ptr<SubSchema> CreateSubSchema() const override;

 protected:
  PropertyMapping CreatePropertyMapping() const override;
};

using ConstantBooleanSchema = ConstantSchema<bool>;
using ConstantIntegerSchema = ConstantSchema<int64_t>;
using ConstantNumberSchema = ConstantSchema<double>;
using ConstantStringSchema = ConstantSchema<std::string>;

extern template class ConstantSchema<bool>;
extern template class ConstantSchema<int64_t>;
extern template class ConstantSchema<double>;
extern template class ConstantSchema<std::string>;

}  // namespace schema
}  // namespace rapidschema

#endif

#endif  // INCLUDE_RAPIDSCHEMA_SCHEMA_CONSTANT_SCHEMA_H_
