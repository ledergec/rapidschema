#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <map>

#include "rapidschema/value.h"
#include "rapidschema/object.h"
#include "rapidschema/no_additional_properties.h"
#include "rapidschema/test_utils.h"
#include "rapidschema/transform_result_matchers.h"

namespace rapidschema {

using testing::Test;
using testing::UnorderedElementsAre;

class NoAdditionalPropertiesTestObject : public NoAdditionalProperties<Object> {
 public:
  Value<int> integer_value;
  Value<std::string> string_value;

 protected:
  std::map<std::string, const Config*> CreateMemberMapping() const override {
    return {{"integerValue", &integer_value},
            {"stringValue", &string_value}};
  }
};

/////////////////////////// Parse DOM Style /////////////////////////////////////////////

TEST(NoAdditionalPropertiesTest, WhenParsingJsonStringWithAdditionalProperties_ThenFailsWithCorrectMessage) {
  NoAdditionalPropertiesTestObject example;
  auto result = ParseConfig(R"(
                {
                  "integerValue": 32,
                  "stringValue": "hallo",
                  "additionalProperty": 23
                }
                )", &example);

  TransformResult expected(Failure("", "Unexpected member encountered: additionalProperty"));
  ASSERT_EQ(expected, result);
}

}  // namespace rapidschema
