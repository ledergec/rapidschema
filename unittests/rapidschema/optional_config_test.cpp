// Copyright (C) 2019 Christian Ledergerber

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <map>

#include "rapidschema/object.h"
#include "rapidschema/optional_config.h"
#include "rapidschema/test_utils.h"
#include "rapidschema/value.h"

namespace rapidschema {

using testing::Test;

class OptionalConfigTestConfigExample : public Object {
 public:
  OptionalConfig<Value<int>> integer_value;
  OptionalConfig<Value<std::string>> string_value;

 protected:
  MemberMapping CreateMemberMapping() const override {
    return {{"integerValue", &integer_value},
            {"stringValue", &string_value}};
  }
};

/////////////////////////// Parse DOM Style /////////////////////////////////////////////

TEST(OptionalConfigTest, GivenMissingMember_WhenParsingObject_ThenOptionalIsEmpty) {
  OptionalConfigTestConfigExample example;
  auto result = ParseConfig(R"(
                {
                  "stringValue": "hallo"
                })", &example);

  ASSERT_TRUE(result.Success());
  ASSERT_FALSE(example.integer_value.HasValue());
  ASSERT_EQ("hallo", example.string_value.GetValue().Get());
}

//////////////////////////// Serialization ///////////////////////////////////////////////


TEST(OptionalConfigTest, WhenSerializeConfig_ThenCorrectString) {
  OptionalConfigTestConfigExample example;
  example.string_value = Value<std::string>();
  example.string_value.GetValue() = "string_value";
  example.integer_value = Value<int>();
  example.integer_value.GetValue() = 434;

  auto jsonstring = SerializeConfig(example);
  auto expected = R"({"integerValue":434,"stringValue":"string_value"})";

  ASSERT_EQ(expected, jsonstring);
}


}  // namespace rapidschema

