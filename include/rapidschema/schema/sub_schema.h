// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_SCHEMA_SUB_SCHEMA_H_
#define INCLUDE_RAPIDSCHEMA_SCHEMA_SUB_SCHEMA_H_

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION

#include "rapidschema/schema/constant_schema.h"
#include "rapidschema/schema/integer_schema.h"
#include "rapidschema/schema/number_schema.h"
#include "rapidschema/schema/string_schema.h"
#include "rapidschema/schema/type_schema.h"

namespace rapidschema {
namespace schema {

class ObjectSchema;
class OneOfSchema;

using SubSchema = OneOf<ObjectSchema,
                        NumberSchema,
                        IntegerSchema,
                        StringSchema,
                        ConstantNumberSchema,
                        ConstantIntegerSchema,
                        ConstantStringSchema,
                        OneOfSchema>;

}  // namespace schema
}  // namespace rapidschema

#endif

#endif  // INCLUDE_RAPIDSCHEMA_SCHEMA_SUB_SCHEMA_H_
