// Copyright (C) 2019 Christian Ledergerber

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "rapidschema/value.h"
#include "rapidschema/string_constraints.h"
#include "rapidschema/schema/schema_assembler.h"
#include "rapidschema/test_utils.h"
#include "rapidschema/transform_result_matchers.h"

namespace rapidschema {

/////////////////////////// Parse DOM Style /////////////////////////////////////////////

TEST(StringConfigValueTest, WhenParsingDomFloat_ThenFails) {
  auto result = TestLeafType<std::string, float>(23.4);
  ASSERT_THAT(result, TransformFailed("Expected type: string. Actual value was: 23.4", ""));
}

TEST(StringConfigValueTest, WhenParsingDomInt_ThenFails) {
  auto result = TestLeafType<std::string, uint32_t>(23);
  ASSERT_THAT(result, TransformFailed("Expected type: string. Actual value was: 23", ""));
}

TEST(StringConfigValueTest, WhenParsingDomNull_ThenFails) {
  auto result = TestLeafType<std::string, std::nullptr_t>(nullptr);
  ASSERT_THAT(result, TransformFailed("Expected type: string. Actual value was: null", ""));
}

TEST(StringConfigValueTest, WhenParsingDomBool_ThenFails) {
  auto result = TestLeafType<std::string, bool>(false);
  ASSERT_THAT(result, TransformFailed("Expected type: string. Actual value was: false", ""));
}

TEST(StringConfigValueTest, GivenNoConstraints_WhenParsingDomString_ThenSuccess) {
  Value<std::string> value;
  auto result = ParseLeaf("ein string", &value);
  ASSERT_THAT(result, TransformSucceeded());
  ASSERT_EQ("ein string", value.Get());
}

/////////////////////////// Validate /////////////////////////////////////////////

TEST(StringConfigValueTest, GivenMinLengthConstraint_WhenValidatingShortString_ThenFails) {
  Value<std::string, MinLength> value;
  value.GetConstraint<MinLength>().SetMinLength(20);
  value = "ein string";
  auto result = value.Validate();
  ASSERT_THAT(result,
      TransformFailed("Expected string of length at least 20. Actual: length 10 string: \"ein string\"", ""));
}

TEST(StringConfigValueTest, GivenMinLengthConstraintUsingMakeValue_WhenValidatingShortString_ThenFails) {
  auto value = MakeValue<std::string, MinLength>(MinLength<>(20));
  value.GetConstraint<MinLength>().SetMinLength(20);
  value = "ein string";
  auto result = value.Validate();
  ASSERT_THAT(result,
      TransformFailed("Expected string of length at least 20. Actual: length 10 string: \"ein string\"", ""));
}

TEST(StringConfigValueTest, GivenMaxLengthConstraint_WhenValidatingLongString_ThenFails) {
  Value<std::string, MaxLength> value;
  value.GetConstraint<MaxLength>().SetMaxLength(2);
  value = "ein string";
  auto result = value.Validate();
  ASSERT_THAT(result,
      TransformFailed("Expected string of length at most 2. Actual: length 10 string: \"ein string\"", ""));
}


/////////////////////////// Serialize Schema /////////////////////////////////////////////

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION
TEST(StringConfigValueTest, WhenSchemaSerialized_ThenCorrectSchema) {
  Value<std::string> value;

  schema::SchemaAssembler assembler;
  auto sub_schema = value.CreateSchema(assembler);
  ASSERT_TRUE(sub_schema->Is<schema::StringSchema>());
  auto type_schema = sub_schema->GetVariant<schema::StringSchema>();
  ASSERT_FALSE(type_schema.min_length.HasValue());
}

TEST(StringConfigValueTest, WhenSchemaWithMinLenghtConstraint_ThenCorrectSchema) {
  auto value = MakeValue<std::string, MinLength>("hallo", MinLength<>(3));

  schema::SchemaAssembler assembler;
  auto sub_schema = value.CreateSchema(assembler);
  ASSERT_TRUE(sub_schema->Is<schema::StringSchema>());
  auto type_schema = sub_schema->GetVariant<schema::StringSchema>();
  ASSERT_TRUE(type_schema.min_length.HasValue());
  ASSERT_EQ(3, type_schema.min_length.GetValue().Get());
}

TEST(StringConfigValueTest, WhenSchemaWithMaxLenghtConstraint_ThenCorrectSchema) {
  auto value = MakeValue<std::string, MaxLength>("hallo", MaxLength<>(3));

  schema::SchemaAssembler assembler;
  auto sub_schema = value.CreateSchema(assembler);
  ASSERT_TRUE(sub_schema->Is<schema::StringSchema>());
  auto type_schema = sub_schema->GetVariant<schema::StringSchema>();
  ASSERT_TRUE(type_schema.max_length.HasValue());
  ASSERT_EQ(3, type_schema.max_length.GetValue().Get());
}
#endif
}  // namespace rapidschema
