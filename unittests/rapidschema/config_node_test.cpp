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

class ConfigExampleTest : public Object {
 public:
  ConfigExampleTest()
  : integer_value(MakeUtf8Value(Maximum(4)))
  , string_value(MakeUtf8Value(MinLength(3), MaxLength(4))) {}

  Value<int, Maximum> integer_value;
  Value<std::string, MinLength, MaxLength> string_value;

 protected:
  std::map<std::string, const Config*> CreateMemberMapping() const override {
    return {{"integerValue", &integer_value},
            {"stringValue", &string_value}};
  }
};

class NestedConfigExampleTest : public Object {
 public:
  NestedConfigExampleTest() {}

  ConfigExampleTest example;
  Value<int> integer_value;
  Value<std::string> string_value;

 protected:
  std::map<std::string, const Config*> CreateMemberMapping() const override {
    return {{"example", &example},
            {"integerValue", &integer_value},
            {"stringValue", &string_value}};
  }
};

class ConfigNodeTest : public Test {
 public:
  ConfigExampleTest example_;
  NestedConfigExampleTest nested_example_;
};

/////////////////////////// Parse DOM Style /////////////////////////////////////////////

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


////////////////////////// Copy Construction and Assignment work ///////////////////////////////////////

TEST_F(ConfigNodeTest, GivenCopiedObject_WhenParsingNestedNode_ThenAllMembersCorrectlySet) {
  NestedConfigExampleTest copied_nested_example(nested_example_);

  auto result = ParseObject(R"(
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

TEST_F(ConfigNodeTest, GivenCopyAssignedObject_WhenParsingNestedNode_ThenAllMembersCorrectlySet) {
  NestedConfigExampleTest copy_assigned_nested_example;

  copy_assigned_nested_example = nested_example_;

  auto result = ParseObject(R"(
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

/////////////////////////// Serialization /////////////////////////////////////////////

TEST_F(ConfigNodeTest, WhenSerialize_ThenCorrectResult) {
    NestedConfigExampleTest node;
    node.integer_value = 123;
    node.string_value = "hallo";
    node.example.integer_value = 443;
    node.example.string_value = "du";

    std::string result = SerializeConfig(node);
    ASSERT_EQ(R"({"example":{"integerValue":443,"stringValue":"du"},"integerValue":123,"stringValue":"hallo"})", result);
}


}  // namespace rapidschema
