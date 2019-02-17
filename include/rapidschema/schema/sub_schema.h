// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_SCHEMA_SCHEMA_H_
#define INCLUDE_RAPIDSCHEMA_SCHEMA_SCHEMA_H_

#include "rapidschema/schema/integer_schema.h"
#include "rapidschema/schema/number_schema.h"
#include "rapidschema/schema/string_schema.h"
#include "rapidschema/schema/type_schema.h"
#include "rapidschema/schema/constant_schema.h"

namespace rapidschema {
namespace schema {

class ObjectSchema;

using SubSchema = OneOf<ObjectSchema,
                        NumberSchema,
                        IntegerSchema,
                        StringSchema,
                        ConstantNumberSchema,
                        ConstantIntegerSchema,
                        ConstantStringSchema>;

}  // namespace schema
}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_SCHEMA_SCHEMA_H_
