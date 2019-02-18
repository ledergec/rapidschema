// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_SCHEMA_SCHEMA_ASSEMBLER_INTERFACE_H_
#define INCLUDE_RAPIDSCHEMA_SCHEMA_SCHEMA_ASSEMBLER_INTERFACE_H_

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION

#include "rapidschema/schema/boolean_schema_interface.h"
#include "rapidschema/schema/constant_schema_interface.h"
#include "rapidschema/schema/integer_schema_interface.h"
#include "rapidschema/schema/number_schema_interface.h"
#include "rapidschema/schema/object_schema_interface.h"
#include "rapidschema/schema/one_of_schema_interface.h"
#include "rapidschema/schema/string_schema_interface.h"

namespace rapidschema {
namespace schema {

class SchemaAssemblerInterface {
 public:
  virtual std::shared_ptr<ConstantBooleanSchemaInterface> CreateConstantBooleanSchema() const = 0;
  virtual std::shared_ptr<ConstantIntegerSchemaInterface> CreateConstantIntegerSchema() const = 0;
  virtual std::shared_ptr<ConstantNumberSchemaInterface> CreateConstantNumberSchema() const = 0;
  virtual std::shared_ptr<ConstantStringSchemaInterface> CreateConstantStringSchema() const = 0;
  virtual std::shared_ptr<BooleanSchemaInterface> CreateBooleanSchema() const = 0;
  virtual std::shared_ptr<IntegerSchemaInterface> CreateIntegerSchema() const = 0;
  virtual std::shared_ptr<NumberSchemaInterface> CreateNumberSchema() const = 0;
  virtual std::shared_ptr<ObjectSchemaInterface> CreateObjectSchema() const = 0;
  virtual std::shared_ptr<OneOfSchemaInterface> CreateOneOfSchema() const = 0;
  virtual std::shared_ptr<StringSchemaInterface> CreateStringSchema() const = 0;
};

}  // namespace schema
}  // namespace rapidschema

#endif

#endif  // INCLUDE_RAPIDSCHEMA_SCHEMA_SCHEMA_ASSEMBLER_INTERFACE_H_
