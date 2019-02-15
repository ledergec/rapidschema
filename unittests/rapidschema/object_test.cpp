// Copyright (C) 2019 Christian Ledergerber

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <map>

#include "rapidschema/value.h"
#include "rapidschema/object.h"
#include "rapidschema/range_constraints.h"
#include "rapidschema/string_constraints.h"
#include "rapidschema/test_utils.h"
#include "rapidschema/transform_result_matchers.h"

namespace rapidschema {

using testing::Test;
using testing::UnorderedElementsAre;

class ObjectTestConfigExample : public Object {
 public:
  ObjectTestConfigExample()
      : integer_value(MakeValue(22, Maximum<int>(4)))
      , string_value(MakeValue(std::string("default"), MinLength<>(3), MaxLength<>(20))) {}

  Value<int, Maximum> integer_value;
  Value<std::string, MinLength, MaxLength> string_value;

 protected:
  PropertyMapping CreatePropertyMapping() const override {
    return {{"integerValue", &integer_value},
            {"stringValue", &string_value}};
  }
};

class ObjectTestNestedConfigExample : public Object {
 public:
  ObjectTestNestedConfigExample() {}

  ObjectTestConfigExample example;
  Value<int> integer_value;
  Value<std::string> string_value;

 protected:
  PropertyMapping CreatePropertyMapping() const override {
    return {{"integerValue", &integer_value},
            {"stringValue", &string_value},
            {"example", &example}};
  }
};

class ObjectTest : public Test {
 public:
  ObjectTestConfigExample example_;
  ObjectTestNestedConfigExample nested_example_;
};

/////////////////////////// Parse DOM Style /////////////////////////////////////////////

TEST_F(ObjectTest, GivenSuccess_WhenParsingObject_ThenAllMembersCorrectlySet) {
  ParseConfig(R"(
                {
                  "integerValue": 23,
                  "stringValue": "hallo"
                }
                )", &example_);

  ASSERT_EQ(23, example_.integer_value.Get());
  ASSERT_EQ("hallo", example_.string_value.Get());
}

TEST_F(ObjectTest, GivenMissingMember_WhenParsingObject_ThenOtherMembersSetCorrectly) {
  ParseConfig(R"(
                {
                  "stringValue": "hallo"
                }
                )", &example_);

  ASSERT_EQ("hallo", example_.string_value.Get());
}

TEST_F(ObjectTest, GivenMissingMember_WhenParsingObject_ThenFailsWithCorrectFailure) {
  auto result = ParseConfig(R"(
                {
                  "stringValue": "hallo"
                }
                )", &example_);

  Result expected(Failure("integerValue", "Value of type int is missing"));
  ASSERT_EQ(expected, result);
}

TEST_F(ObjectTest, GivenParsingMemberFails_WhenParsingObject_ThenFailsWithCorrectFailure) {
  auto result = ParseConfig(R"(
                {
                  "integerValue": "shouldBeInt",
                  "stringValue": "hallo"
                }
                )", &example_);

  Result expected(Failure("integerValue", "Expected type: int. Actual value was: \"shouldBeInt\""));
  ASSERT_EQ(expected, result);
}

TEST_F(ObjectTest, GivenSuccess_WhenParsingNestedObject_ThenAllMembersCorrectlySet) {
  auto result = ParseConfig(R"(
                {
                  "example": {
                    "integerValue": 43,
                    "stringValue": "nested_value"
                  },
                  "integerValue": 23,
                  "stringValue": "hallo"
                }
                )", &nested_example_);

  ASSERT_EQ(43, nested_example_.example.integer_value.Get());
  ASSERT_EQ("nested_value", nested_example_.example.string_value.Get());
  ASSERT_EQ(23, nested_example_.integer_value.Get());
  ASSERT_EQ("hallo", nested_example_.string_value.Get());
}

TEST_F(ObjectTest, GivenMissingMember_WhenParsingNestedObject_ThenOtherMembersSetCorrectly) {
  auto result = ParseConfig(R"(
                {
                  "example": {
                    "stringValue": "nested_value"
                  },
                  "integerValue": 23,
                  "stringValue": "hallo"
                }
                )", &nested_example_);

  ASSERT_EQ("nested_value", nested_example_.example.string_value.Get());
  ASSERT_EQ(23, nested_example_.integer_value.Get());
  ASSERT_EQ("hallo", nested_example_.string_value.Get());
}

TEST_F(ObjectTest, GivenMissingMember_WhenParsingNestedObject_ThenFailsWithCorrectFailure) {
  auto result = ParseConfig(R"(
                {
                  "example": {
                    "stringValue": "nested_value"
                  },
                  "integerValue": 23,
                  "stringValue": "hallo"
                }
                )", &nested_example_);

  Result expected(Failure("example.integerValue", "Value of type int is missing"));
  ASSERT_EQ(expected, result);
}

TEST_F(ObjectTest, GivenParsingMemberFails_WhenParsingNestedObject_ThenFailsWithCorrectFailure) {
  auto result = ParseConfig(R"(
                {
                  "example": {
                    "integerValue": "shouldBeInt",
                    "stringValue": "nested_value"
                  },
                  "integerValue": 23,
                  "stringValue": "hallo"
                }
                )", &nested_example_);

  Result expected(Failure("example.integerValue", "Expected type: int. Actual value was: \"shouldBeInt\""));
  ASSERT_EQ(expected, result);
}


////////////////////////// Copy Construction and Assignment work ///////////////////////////////////////

TEST_F(ObjectTest, GivenCopiedObject_WhenParsingNestedObject_ThenAllMembersCorrectlySet) {
  ObjectTestNestedConfigExample copied_nested_example(nested_example_);

  auto result = ParseConfig(R"(
                {
                  "example": {
                    "integerValue": 43,
                    "stringValue": "nested_value"
                  },
                  "integerValue": 23,
                  "stringValue": "hallo"
                }
                )", &copied_nested_example);

  ASSERT_EQ(43, copied_nested_example.example.integer_value.Get());
  ASSERT_EQ("nested_value", copied_nested_example.example.string_value.Get());
  ASSERT_EQ(23, copied_nested_example.integer_value.Get());
  ASSERT_EQ("hallo", copied_nested_example.string_value.Get());
}

TEST_F(ObjectTest, GivenCopyAssignedObject_WhenParsingNestedObject_ThenAllMembersCorrectlySet) {
  ObjectTestNestedConfigExample copy_assigned_nested_example;

  copy_assigned_nested_example = nested_example_;

  auto result = ParseConfig(R"(
                {
                  "example": {
                    "integerValue": 43,
                    "stringValue": "nested_value"
                  },
                  "integerValue": 23,
                  "stringValue": "hallo"
                }
                )", &copy_assigned_nested_example);

  ASSERT_EQ(43, copy_assigned_nested_example.example.integer_value.Get());
  ASSERT_EQ("nested_value", copy_assigned_nested_example.example.string_value.Get());
  ASSERT_EQ(23, copy_assigned_nested_example.integer_value.Get());
  ASSERT_EQ("hallo", copy_assigned_nested_example.string_value.Get());
}

TEST_F(ObjectTest, GivenMemoryCollected_WhenParsingNestedObject_ThenAllMembersCorrectlySet) {
  auto result = ParseConfig(R"(
                {
                  "example": {
                    "integerValue": 0,
                    "stringValue": ""
                  },
                  "integerValue": 0,
                  "stringValue": ""
                }
                )", &nested_example_);

  ASSERT_TRUE(result.Success());

  nested_example_.CollectMemory();

  result = ParseConfig(R"(
                {
                  "example": {
                    "integerValue": 43,
                    "stringValue": "nested_value"
                  },
                  "integerValue": 23,
                  "stringValue": "hallo"
                }
                )", &nested_example_);

  ASSERT_TRUE(result.Success());
  ASSERT_EQ(43, nested_example_.example.integer_value.Get());
  ASSERT_EQ("nested_value", nested_example_.example.string_value.Get());
  ASSERT_EQ(23, nested_example_.integer_value.Get());
  ASSERT_EQ("hallo", nested_example_.string_value.Get());
}

/////////////////////////// Validation /////////////////////////////////////////////

TEST_F(ObjectTest, WhenValidateFails_ThenErrorsReportedWithCorrectPath) {
  example_.integer_value = 20;
  auto result = example_.Validate();
  ASSERT_THAT(result, TransformFailed("Expected: <= 4. Actual: 20", "integerValue"));
}

/////////////////////////// Serialization /////////////////////////////////////////////

TEST_F(ObjectTest, WhenSerialize_ThenCorrectResult) {
  ObjectTestNestedConfigExample node;
  node.integer_value = 123;
  node.string_value = "hallo";
  node.example.integer_value = 443;
  node.example.string_value = "du";

  std::string result = SerializeConfig(node);
  ASSERT_EQ(R"({"integerValue":123,"stringValue":"hallo","example":{"integerValue":443,"stringValue":"du"}})", result);
}

}  // namespace rapidschema
