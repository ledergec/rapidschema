// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_SCHEMA_ONE_OF_SCHEMA_H_
#define INCLUDE_RAPIDSCHEMA_SCHEMA_ONE_OF_SCHEMA_H_

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION

#include "rapidschema/schema/one_of_schema_interface.h"

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