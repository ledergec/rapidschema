// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_SCHEMA_SUB_SCHEMA_H_
#define INCLUDE_RAPIDSCHEMA_SCHEMA_SUB_SCHEMA_H_

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION

#include <memory>

#include "rapidschema/schema/boolean_schema.h"
#include "rapidschema/schema/constant_schema.h"
#include "rapidschema/schema/integer_schema.h"
#include "rapidschema/schema/number_schema.h"
#include "rapidschema/schema/one_of_schema.h"
#include "rapidschema/schema/string_schema.h"
#include "rapidschema/one_of.h"

namespace rapidschema {
namespace schema {

class SubSchema : public OneOf<ObjectSchema,
                               BooleanSchema,
                               IntegerSchema,
                               NumberSchema,
                               StringSchema,
                               ConstantBooleanSchema,
                               ConstantIntegerSchema,
                               ConstantNumberSchema,
                               ConstantStringSchema,
                               OneOfSchema> {
 public:
  SubSchema() = default;

  template <typename SchemaType>
  explicit SubSchema(const SchemaType& schema)
    : GenericOneOf(schema) {}
};

}  // namespace schema
}  // namespace rapidschema

#endif

#endif  // INCLUDE_RAPIDSCHEMA_SCHEMA_SUB_SCHEMA_H_
