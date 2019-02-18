// Copyright (C) 2019 Christian Ledergerber

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION

#include "rapidschema/schema/schema.h"

namespace rapidschema {
namespace schema {

std::shared_ptr<SubSchema> OneOfSchema::CreateSubSchema() const {
  return std::make_shared<SubSchema>(*this);
}
using OneOfSubSchema = OneOf<ObjectSchema,
                             NumberSchema,
                             IntegerSchema,
                             StringSchema,
                             ConstantNumberSchema,
                             ConstantIntegerSchema,
                             ConstantStringSchema>;

Array<OneOfSubSchema> one_of;

void OneOfSchema::AddVariant(std::shared_ptr<SubSchema> sub_schema) {
  if (sub_schema->Is<ObjectSchema>()) {
    one_of.push_back(OneOfSubSchema(sub_schema->GetVariant<ObjectSchema>()));
  } else if (sub_schema->Is<NumberSchema>()) {
    one_of.push_back(OneOfSubSchema(sub_schema->GetVariant<NumberSchema>()));
  } else if (sub_schema->Is<IntegerSchema>()) {
    one_of.push_back(OneOfSubSchema(sub_schema->GetVariant<IntegerSchema>()));
  } else if (sub_schema->Is<StringSchema>()) {
    one_of.push_back(OneOfSubSchema(sub_schema->GetVariant<StringSchema>()));
  } else if (sub_schema->Is<ConstantNumberSchema>()) {
    one_of.push_back(OneOfSubSchema(sub_schema->GetVariant<ConstantNumberSchema>()));
  } else if (sub_schema->Is<ConstantIntegerSchema>()) {
    one_of.push_back(OneOfSubSchema(sub_schema->GetVariant<ConstantIntegerSchema>()));
  } else if (sub_schema->Is<ConstantStringSchema>()) {
    one_of.push_back(OneOfSubSchema(sub_schema->GetVariant<ConstantStringSchema>()));
  } else {
    assert(false);
  }
}

OneOfSchema::PropertyMapping OneOfSchema::CreatePropertyMapping() const {
  return {{"oneOf", &one_of}};
}

}  // namespace schema
}  // namespace rapidschema

#endif
