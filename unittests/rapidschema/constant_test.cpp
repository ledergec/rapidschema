// Copyright (C) 2019 Christian Ledergerber

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "rapidschema/constant.h"
#include "rapidschema/object.h"
#include "rapidschema/test_utils.h"
#include "rapidschema/schema/schema.h"
#include "rapidschema/schema/schema_assembler.h"
#include "rapidschema/transform_result_matchers.h"
#include "rapidschema/value.h"

namespace rapidschema {

using testing::AnyOf;
using testing::Eq;
using testing::Test;

class ConstantTestConfigExample : public Object {
 public:
  ConstantTestConfigExample() {
    integer_value.SetExpectedValue(12);
    string_value.SetExpectedValue("string_value");
  }

  Constant<int> integer_value;
  Constant<std::string> string_value;

 protected:
  PropertyMapping CreatePropertyMapping() const override {
    return {{"integerValue", &integer_value},
            {"stringValue", &string_value}};
  }
};

/////////////////////////// Parse DOM Style /////////////////////////////////////////////


TEST(ConstantTest, GivenEqualToConstant_WhenParsing_ThenValidationSucceeds) {
  ConstantTestConfigExample example;
  auto result = ParseConfig(R"(
                {
                  "integerValue": 12,
                  "stringValue": "string_value"
                })", &example);
  ASSERT_TRUE(result.Success());

  result = example.Validate();
  ASSERT_TRUE(result.Success());
}

TEST(ConstantTest, GivenNotEqualToConstant_WhenParsing_ThenValidationFails) {
  ConstantTestConfigExample example;
  auto result = ParseConfig(R"(
                {
                  "integerValue": 23,
                  "stringValue": "hallo"
                })", &example);
  ASSERT_FALSE(result.Success());

  ASSERT_EQ(2, result.GetFailures().size());
  ASSERT_THAT("Expected constant value: string_value, actual: hallo.",
              AnyOf(Eq(result.GetFailures()[0].GetMessage()), Eq(result.GetFailures()[1].GetMessage())));
  ASSERT_THAT("Expected constant value: 12, actual: 23.",
              AnyOf(Eq(result.GetFailures()[0].GetMessage()), Eq(result.GetFailures()[1].GetMessage())));
}

/////////////////////////// Serialize Schema /////////////////////////////////////////////

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION
TEST(ConstantTest, GivenBooleanConstant_WhenSchemaSerialized_ThenCorrectSchema) {
  Constant<bool> constant;
  constant.SetExpectedValue(true);

  schema::SchemaAssembler assembler;
  auto sub_schema = constant.CreateSchema(assembler);
  ASSERT_TRUE(sub_schema->Is<schema::ConstantBooleanSchema>());
  auto type_schema = sub_schema->GetVariant<schema::ConstantBooleanSchema>();
  ASSERT_EQ(true, type_schema.const_value.Get());
}

TEST(ConstantTest, GivenIntConstant_WhenSchemaSerialized_ThenCorrectSchema) {
  Constant<int> constant;
  constant.SetExpectedValue(12);

  schema::SchemaAssembler assembler;
  auto sub_schema = constant.CreateSchema(assembler);
  ASSERT_TRUE(sub_schema->Is<schema::ConstantIntegerSchema>());
  auto type_schema = sub_schema->GetVariant<schema::ConstantIntegerSchema>();
  ASSERT_EQ(12, type_schema.const_value.Get());
}

TEST(ConstantTest, GivenNumberConstant_WhenSchemaSerialized_ThenCorrectSchema) {
  Constant<double> constant;
  constant.SetExpectedValue(12.4);

  schema::SchemaAssembler assembler;
  auto sub_schema = constant.CreateSchema(assembler);
  ASSERT_TRUE(sub_schema->Is<schema::ConstantNumberSchema>());
  auto type_schema = sub_schema->GetVariant<schema::ConstantNumberSchema>();
  ASSERT_EQ(12.4, type_schema.const_value.Get());
}

TEST(ConstantTest, GivenStringConstant_WhenSchemaSerialized_ThenCorrectSchema) {
  Constant<std::string> constant;
  constant.SetExpectedValue("hallo");

  schema::SchemaAssembler assembler;
  auto sub_schema = constant.CreateSchema(assembler);
  ASSERT_TRUE(sub_schema->Is<schema::ConstantStringSchema>());
  auto type_schema = sub_schema->GetVariant<schema::ConstantStringSchema>();
  ASSERT_EQ("hallo", type_schema.const_value.Get());
}
#endif

}  // namespace rapidschema

