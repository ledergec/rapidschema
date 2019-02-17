// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_SCHEMA_SUB_SCHEMA_H_
#define INCLUDE_RAPIDSCHEMA_SCHEMA_SUB_SCHEMA_H_

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION

#include <memory>

#include "rapidschema/array.h"
#include "rapidschema/no_additional_properties.h"
#include "rapidschema/object.h"
#include "rapidschema/one_of.h"
#include "rapidschema/pattern_property.h"
#include "rapidschema/optional_config.h"

namespace rapidschema {
namespace schema {

class SubSchema : public OneOf<ObjectSchema,
                               NumberSchema,
                               IntegerSchema,
                               StringSchema,
                               ConstantNumberSchema,
                               ConstantIntegerSchema,
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
