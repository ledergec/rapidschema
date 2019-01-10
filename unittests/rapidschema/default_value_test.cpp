#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <map>

#include "rapidschema/default_value.h"
#include "rapidschema/object.h"
#include "rapidschema/test_utils.h"
#include "rapidschema/value.h"

namespace rapidschema {

using testing::Test;

class DefaultTestConfigExample : public Object {
 public:
  DefaultTestConfigExample() {
    integer_value = 12;
    string_value = "string_value";
  }

  DefaultValue<int> integer_value;
  DefaultValue<std::string> string_value;

 protected:
  std::map<std::string, const Config*> CreateMemberMapping() const override {
    return {{"integerValue", &integer_value},
            {"stringValue", &string_value}};
  }
};

/////////////////////////// Parse DOM Style /////////////////////////////////////////////

TEST(DefaultTest, GivenMissingMember_WhenParsingObject_ThenSetToDefault) {
  DefaultTestConfigExample example;
  auto result = ParseConfig(R"(
                {
                  "stringValue": "hallo"
                })", &example);

  ASSERT_TRUE(result.Success());
  ASSERT_EQ(12, example.integer_value.Get());
  ASSERT_EQ("hallo", example.string_value.Get());
}

}  // namespace rapidschema

