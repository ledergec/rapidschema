// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_SCHEMA_SCHEMA_ASSEMBLER_H_
#define INCLUDE_RAPIDSCHEMA_SCHEMA_SCHEMA_ASSEMBLER_H_

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION

#include "rapidschema/schema/boolean_schema.h"
#include "rapidschema/schema/constant_schema.h"
#include "rapidschema/schema/integer_schema.h"
#include "rapidschema/schema/number_schema.h"
#include "rapidschema/schema/object_schema.h"
#include "rapidschema/schema/one_of_schema.h"
#include "rapidschema/schema/string_schema.h"
#include "rapidschema/schema/schema_assembler_interface.h"

namespace rapidschema {
namespace schema {

class SchemaAssembler : public SchemaAssemblerInterface {
 public:
  std::shared_ptr<ConstantBooleanSchemaInterface> CreateConstantBooleanSchema() const override {
    return std::make_shared<ConstantBooleanSchema>();
  }

  std::shared_ptr<ConstantIntegerSchemaInterface> CreateConstantIntegerSchema() const override {
    return std::make_shared<ConstantIntegerSchema>();
  }

  std::shared_ptr<ConstantNumberSchemaInterface> CreateConstantNumberSchema() const override {
    return std::make_shared<ConstantNumberSchema>();
  }

  std::shared_ptr<ConstantStringSchemaInterface> CreateConstantStringSchema() const override {
    return std::make_shared<ConstantStringSchema>();
  }

  std::shared_ptr<BooleanSchemaInterface> CreateBooleanSchema() const override {
    return std::make_shared<BooleanSchema>();
  }

  std::shared_ptr<IntegerSchemaInterface> CreateIntegerSchema() const override {
    return std::make_shared<IntegerSchema>();
  }

  std::shared_ptr<NumberSchemaInterface> CreateNumberSchema() const override {
    return std::make_shared<NumberSchema>();
  }

  std::shared_ptr<ObjectSchemaInterface> CreateObjectSchema() const override {
    return std::make_shared<ObjectSchema>();
  }

  std::shared_ptr<OneOfSchemaInterface> CreateOneOfSchema() const override {
    return std::make_shared<OneOfSchema>();
  }

  std::shared_ptr<StringSchemaInterface> CreateStringSchema() const override {
    return std::make_shared<StringSchema>();
  }
};

}  // namespace schema
}  // namespace rapidschema

#endif

#endif  // INCLUDE_RAPIDSCHEMA_SCHEMA_SCHEMA_ASSEMBLER_H_
