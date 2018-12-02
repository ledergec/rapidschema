#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "rapidschema/configvalue.h"
#include "rapidschema/confignode.h"
#include "rapidschema/range_constraints.h"
#include "rapidschema/string_constraints.h"
#include "rapidschema/test_utils.h"
#include "rapidschema/transform_result_matchers.h"

namespace rapidschema {

using testing::Test;

class ConfigExampleTest : public ConfigNode {
 public:
  ConfigExampleTest()
      : ConfigNode("example", {&integer_value, &string_value})
      , integer_value(MakeValue("integerValue", Maximum(4)))
      , string_value(MakeValue("stringValue", MinLength(3), MaxLength(4))) {}

  ConfigValue<int, Maximum> integer_value;
  ConfigValue<std::string, MinLength, MaxLength> string_value;
};

class NestedConfigExampleTest : public ConfigNode {
 public:
  NestedConfigExampleTest()
      : ConfigNode("nestedExample", {&example, &integer_value, &string_value})
      , integer_value("integerValue")
      , string_value("stringValue") {}

  ConfigExampleTest example;
  ConfigValue<int> integer_value;
  ConfigValue<std::string> string_value;
};

class ConfigNodeTest : public Test {
 public:
  ConfigExampleTest example_;
  NestedConfigExampleTest nested_example_;
};

TEST_F(ConfigNodeTest, GivenSuccess_WhenParsingNode_ThenAllMembersCorrectlySet) {
    ParseObject(R"(
                {
                  "integerValue": 23,
                  "stringValue": "hallo"
                }
                )", &example_);

    ASSERT_EQ(23, example_.integer_value.Get());
    ASSERT_EQ("hallo", example_.string_value.Get());
}

TEST_F(ConfigNodeTest, GivenMissingMember_WhenParsingNode_ThenOtherMembersSetCorrectly) {
    ParseObject(R"(
                {
                  "stringValue": "hallo"
                }
                )", &example_);

    ASSERT_EQ(23, example_.integer_value.Get());
}

TEST_F(ConfigNodeTest, GivenMissingMember_WhenParsingNode_ThenFailsWithCorrectFailure) {
    auto result = ParseObject(R"(
                {
                  "stringValue": "hallo"
                }
                )", &example_);

    TransformResult expected(Failure("Missing member: \"integerValue\""));
    ASSERT_EQ(expected, result);
}

TEST_F(ConfigNodeTest, GivenParsingMemberFails_WhenParsingNode_ThenFailsWithCorrectFailure) {
    auto result = ParseObject(R"(
                {
                  "integerValue": "shouldBeInt",
                  "stringValue": "hallo"
                }
                )", &example_);

    TransformResult expected(Failure("integerValue", "Expected type: int. Actual value was: \"shouldBeInt\""));
    ASSERT_EQ(expected, result);
}

TEST_F(ConfigNodeTest, GivenSuccess_WhenParsingNestedNode_ThenAllMembersCorrectlySet) {
    auto result = ParseObject(R"(
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

TEST_F(ConfigNodeTest, GivenMissingMember_WhenParsingNestedNode_ThenOtherMembersSetCorrectly) {
    auto result = ParseObject(R"(
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

TEST_F(ConfigNodeTest, GivenMissingMember_WhenParsingNestedNode_ThenFailsWithCorrectFailure) {
    auto result = ParseObject(R"(
                {
                  "example": {
                    "stringValue": "nested_value"
                  },
                  "integerValue": 23,
                  "stringValue": "hallo"
                }
                )", &nested_example_);

    TransformResult expected(Failure("example", "Missing member: \"integerValue\""));
    ASSERT_EQ(expected, result);
}

TEST_F(ConfigNodeTest, GivenParsingMemberFails_WhenParsingNestedNode_ThenFailsWithCorrectFailure) {
    auto result = ParseObject(R"(
                {
                  "example": {
                    "integerValue": "shouldBeInt",
                    "stringValue": "nested_value"
                  },
                  "integerValue": 23,
                  "stringValue": "hallo"
                }
                )", &nested_example_);

    TransformResult expected(Failure("example.integerValue", "Expected type: int. Actual value was: \"shouldBeInt\""));
    ASSERT_EQ(expected, result);
}

}  // namespace rapidschema
