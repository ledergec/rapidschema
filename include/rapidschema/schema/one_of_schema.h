// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_SCHEMA_ONE_OF_SCHEMA_H_
#define INCLUDE_RAPIDSCHEMA_SCHEMA_ONE_OF_SCHEMA_H_

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION

#include <memory>

#include "rapidschema/array.h"
#include "rapidschema/one_of.h"
#include "rapidschema/schema/constant_schema.h"
#include "rapidschema/schema/integer_schema.h"
#include "rapidschema/schema/number_schema.h"
#include "rapidschema/schema/object_schema.h"
#include "rapidschema/schema/one_of_schema_interface.h"
#include "rapidschema/schema/string_schema.h"
#include "rapidschema/object.h"

namespace rapidschema {
namespace schema {

class OneOfSchema : public NoAdditionalProperties<Object> ,
                    public OneOfSchemaInterface {
 public:
  using OneOfSubSchema = OneOf<ObjectSchema,
                               NumberSchema,
                               IntegerSchema,
                               StringSchema,
                               ConstantNumberSchema,
                               ConstantIntegerSchema,
                               ConstantStringSchema>;

  Array<OneOfSubSchema> one_of;

  void AddVariant(std::shared_ptr<SubSchema> sub_schema) override;

  std::shared_ptr<SubSchema> CreateSubSchema() const override;

 protected:
  PropertyMapping CreatePropertyMapping() const override;
};

}  // namespace schema
}  // namespace rapidschema

#endif

#endif  // INCLUDE_RAPIDSCHEMA_SCHEMA_ONE_OF_SCHEMA_H_
