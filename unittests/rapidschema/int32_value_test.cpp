// Copyright (C) 2019 Christian Ledergerber

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "rapidschema/multiple_of_constraint.h"
#include "rapidschema/object.h"
#include "rapidschema/range_constraints.h"
#include "rapidschema/schema/schema_assembler.h"
#include "rapidschema/test_utils.h"
#include "rapidschema/transform_result_matchers.h"
#include "rapidschema/value.h"

namespace rapidschema {

/////////////////////////// Parse DOM Style /////////////////////////////////////////////

TEST(Int32ConfigValueTest, WhenParsingDomFloat_ThenFails) {
  auto result = TestLeafType<int32_t, float>(23.4);
  ASSERT_THAT(result, TransformFailed("Expected type: int. Actual value was: 23.4", ""));
}

TEST(Int32ConfigValueTest, WhenParsingDomString_ThenFails) {
  auto result = TestLeafType<int32_t, std::string>("ein string");
  ASSERT_THAT(result, TransformFailed("Expected type: int. Actual value was: \"ein string\"", ""));
}

TEST(Int32ConfigValueTest, WhenParsingDomNull_ThenFails) {
  auto result = TestLeafType<int32_t, std::nullptr_t>(nullptr);
  ASSERT_THAT(result, TransformFailed("Expected type: int. Actual value was: null", ""));
}

TEST(Int32ConfigValueTest, WhenParsingDomBool_ThenFails) {
  auto result = TestLeafType<int32_t, bool>(false);
  ASSERT_THAT(result, TransformFailed("Expected type: int. Actual value was: false", ""));
}

TEST(Int32ConfigValueTest, WhenParsingDomOutOfLowerRange_ThenFails) {
  auto out_of_range = static_cast<int64_t>(std::numeric_limits<int32_t>::min()) - 1;
  auto result = TestLeafType<int32_t, int64_t>(out_of_range);
  ASSERT_THAT(result, TransformFailed("Expected type: int. Actual value was: -2147483649", ""));
}

TEST(Int32ConfigValueTest, WhenParsingDomOutOfUpperRange_ThenFails) {
  auto out_of_range = static_cast<int64_t>(std::numeric_limits<int32_t>::max()) + 1;
  auto result = TestLeafType<int32_t, int64_t>(out_of_range);
  ASSERT_THAT(result, TransformFailed("Expected type: int. Actual value was: 2147483648", ""));
}

TEST(Int32ConfigValueTest, WhenParsing23_ThenParsedCorrectly) {
  auto result = TestLeafType<int32_t, int32_t>(23);
  ASSERT_THAT(result, TransformSucceeded());
}

TEST(Int32ConfigValueTest, WhenParsingLowerLimit_ThenParsedCorrectly) {
  auto result = TestLeafType<int32_t, int32_t>(std::numeric_limits<int32_t>::min());
  ASSERT_THAT(result, TransformSucceeded());
}

TEST(Int32ConfigValueTest, WhenParsingUpperLimit_ThenParsedCorrectly) {
  auto result = TestLeafType<int32_t, int32_t>(std::numeric_limits<int32_t>::max());
  ASSERT_THAT(result, TransformSucceeded());
}

/////////////////////////// Serialization /////////////////////////////////////////////

class Int32ConfigValueTestNode : public Object {
 public:
  Value<int32_t> value;

 protected:
  PropertyMapping CreatePropertyMapping() const override {
    return {{"value", &value}};
  }
};

TEST(Int32ConfigValueTest, WhenSerialize_ThenCorrectResult) {
  Int32ConfigValueTestNode node;
  node.value = 123;
  std::string result = SerializeConfig(node);
  ASSERT_EQ(R"({"value":123})", result);
}

/////////////////////////// Serialize Schema /////////////////////////////////////////////

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION
TEST(Int32ConfigValueTest, WhenSchemaSerialized_ThenCorrectSchema) {
  Value<int32_t> value;

  schema::SchemaAssembler assembler;
  auto sub_schema = value.CreateSchema(assembler);
  ASSERT_TRUE(sub_schema->Is<schema::IntegerSchema>());
  auto type_schema = sub_schema->GetVariant<schema::IntegerSchema>();
  ASSERT_FALSE(type_schema.multiple_of.HasValue());
}

TEST(Int32ConfigValueTest, WhenSchemaWithExclusiveMinimumConstraintSerialized_ThenCorrectSchema) {
  auto value = MakeValue<double, ExclusiveMinimum>(32, ExclusiveMinimum<double>(45));

  schema::SchemaAssembler assembler;
  auto sub_schema = value.CreateSchema(assembler);
  ASSERT_TRUE(sub_schema->Is<schema::NumberSchema>());
  auto type_schema = sub_schema->GetVariant<schema::NumberSchema>();
  ASSERT_TRUE(type_schema.exclusive_minimum.HasValue());
  ASSERT_EQ(45, type_schema.exclusive_minimum.GetValue().Get());
}

TEST(Int32ConfigValueTest, WhenSchemaWithMaximum_ThenCorrectSchema) {
  auto value = MakeValue<int, Maximum>(32, Maximum<int>(3));

  schema::SchemaAssembler assembler;
  auto sub_schema = value.CreateSchema(assembler);
  ASSERT_TRUE(sub_schema->Is<schema::IntegerSchema>());
  auto type_schema = sub_schema->GetVariant<schema::IntegerSchema>();
  ASSERT_TRUE(type_schema.maximum.HasValue());
  ASSERT_EQ(3, type_schema.maximum.GetValue().Get());
}

TEST(Int32ConfigValueTest, WhenSchemaWithMultipleOfConstraintSerialized_ThenCorrectSchema) {
  auto value = MakeValue<int, MultipleOf>(32, MultipleOf<int>(3));

  schema::SchemaAssembler assembler;
  auto sub_schema = value.CreateSchema(assembler);
  ASSERT_TRUE(sub_schema->Is<schema::IntegerSchema>());
  auto type_schema = sub_schema->GetVariant<schema::IntegerSchema>();
  ASSERT_TRUE(type_schema.multiple_of.HasValue());
  ASSERT_EQ(3, type_schema.multiple_of.GetValue().Get());
}

TEST(Int32ConfigValueTest, WhenSchemaWithMultipleConstraintSerialized_ThenCorrectSchema) {
  auto value = MakeValue<int, Minimum, ExclusiveMaximum>(32, Minimum<int>(3), ExclusiveMaximum<int>(45));

  schema::SchemaAssembler assembler;
  auto sub_schema = value.CreateSchema(assembler);
  ASSERT_TRUE(sub_schema->Is<schema::IntegerSchema>());
  auto type_schema = sub_schema->GetVariant<schema::IntegerSchema>();
  ASSERT_FALSE(type_schema.multiple_of.HasValue());
  ASSERT_TRUE(type_schema.minimum.HasValue());
  ASSERT_EQ(3, type_schema.minimum.GetValue().Get());
  ASSERT_TRUE(type_schema.exclusive_maximum.HasValue());
  ASSERT_EQ(45, type_schema.exclusive_maximum.GetValue().Get());
}
#endif

}  // namespace rapidschema
