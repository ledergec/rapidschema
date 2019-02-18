// Copyright (C) 2019 Christian Ledergerber

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "rapidschema/object.h"
#include "rapidschema/value.h"
#include "rapidschema/range_constraints.h"
#include "rapidschema/schema/schema_assembler.h"
#include "rapidschema/test_utils.h"
#include "rapidschema/transform_result_matchers.h"

namespace rapidschema {

/////////////////////////// Parse DOM Style /////////////////////////////////////////////

TEST(Int64ConfigValueTest, WhenParsingDomFloat_ThenFails) {
  auto result = TestLeafType<int64_t, float>(23.4);
  ASSERT_THAT(result, TransformFailed("Expected type: long int. Actual value was: 23.4", ""));
}

TEST(Int64ConfigValueTest, WhenParsingDomString_ThenFails) {
  auto result = TestLeafType<int64_t, std::string>("ein string");
  ASSERT_THAT(result, TransformFailed("Expected type: long int. Actual value was: \"ein string\"", ""));
}

TEST(Int64ConfigValueTest, WhenParsingDomNull_ThenFails) {
  auto result = TestLeafType<int64_t, std::nullptr_t>(nullptr);
  ASSERT_THAT(result, TransformFailed("Expected type: long int. Actual value was: null", ""));
}

TEST(Int64ConfigValueTest, WhenParsingDomBool_ThenFails) {
  auto result = TestLeafType<int64_t, bool>(false);
  ASSERT_THAT(result, TransformFailed("Expected type: long int. Actual value was: false", ""));
}

TEST(Int64ConfigValueTest, WhenParsingDomOutOfLowerRange_ThenFails) {
  auto json = R"({"leaf": -9223372036854775809})";
  Value<int64_t> value;
  auto result = ParseJsonLeaf(json, &value);
  ASSERT_FALSE(result.Success());
}

TEST(Int64ConfigValueTest, WhenParsingDomLowerRange_ThenSucceeds) {
  auto json = R"({"leaf": -9223372036854775807})";
  Value<int64_t> value;
  auto result = ParseJsonLeaf(json, &value);
  ASSERT_THAT(result, TransformSucceeded());
}

TEST(Int64ConfigValueTest, WhenParsingDomOutOfUpperRange_ThenFails) {
  auto json = R"({"leaf": 9223372036854775808})";
  Value<int64_t> value;
  auto result = ParseJsonLeaf(json, &value);
  ASSERT_FALSE(result.Success());
}

TEST(Int64ConfigValueTest, WhenParsingDomUpperRange_ThenSucceeds) {
  auto json = R"({"leaf": 9223372036854775806})";
  Value<int64_t> value;
  auto result = ParseJsonLeaf(json, &value);
  ASSERT_THAT(result, TransformSucceeded());
}

TEST(Int64ConfigValueTest, WhenParsingDom23_ThenParsedCorrectly) {
  auto result = TestLeafType<int64_t, int64_t>(23);
  ASSERT_THAT(result, TransformSucceeded());
}

TEST(Int64ConfigValueTest, WhenParsingDomLowerLimit_ThenParsedCorrectly) {
  auto result = TestLeafType<int64_t, int64_t>(std::numeric_limits<int64_t>::min());
  ASSERT_THAT(result, TransformSucceeded());
}

TEST(Int64ConfigValueTest, WhenParsingDomUpperLimit_ThenParsedCorrectly) {
  auto result = TestLeafType<int64_t, int64_t>(std::numeric_limits<int64_t>::max());
  ASSERT_THAT(result, TransformSucceeded());
}

/////////////////////////// Serialization /////////////////////////////////////////////

class Int64ConfigValueTestNode : public Object {
 public:
  Value<int64_t> value;

 protected:
  PropertyMapping CreatePropertyMapping() const override {
    return {{"value", &value}};
  }
};

TEST(Int64ConfigValueTest, WhenSerialize_ThenCorrectResult) {
  Int64ConfigValueTestNode node;
  node.value = 123;
  std::string result = SerializeConfig(node);
  ASSERT_EQ(R"({"value":123})", result);
}

/////////////////////////// Serialize Schema /////////////////////////////////////////////

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION
TEST(Int64ConfigValueTest, WhenSchemaSerialized_ThenCorrectSchema) {
  Value<int64_t> value;

  schema::SchemaAssembler assembler;
  auto sub_schema = value.CreateSchema(assembler);
  ASSERT_TRUE(sub_schema->Is<schema::IntegerSchema>());
  auto type_schema = sub_schema->GetVariant<schema::IntegerSchema>();
  ASSERT_FALSE(type_schema.multiple_of.HasValue());
}
#endif

}  // namespace rapidschema
