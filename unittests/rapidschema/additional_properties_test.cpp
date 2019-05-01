// Copyright (C) 2019 Christian Ledergerber

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <map>

#include "rapidschema/additional_properties.h"
#include "rapidschema/no_additional_properties.h"
#include "rapidschema/object.h"
#include "rapidschema/ostream_operators.h"
#include "rapidschema/test_utils.h"
#include "rapidschema/value.h"

namespace rapidschema {

using testing::Test;
using testing::UnorderedElementsAre;

class AdditionalPropertiesTestObject : public NoAdditionalProperties<Object> {
 public:
  Value<int> integer_value;
  Value<std::string> string_value;

 protected:
  PropertyMapping CreatePropertyMapping() const override {
    return {{"integerValue", &integer_value},
            {"stringValue", &string_value}};
  }
};

/////////////////////////// Parse DOM Style /////////////////////////////////////////////

TEST(NoAdditionalPropertiesTest,
    GivenNoAdditionalPropertiesAllowed_WhenParsingAdditionalProperties_ThenFailsWithCorrectMessage) {
  AdditionalPropertiesTestObject example;
  auto result = ParseConfig(R"(
                {
                  "integerValue": 32,
                  "stringValue": "hallo",
                  "additionalProperty": 23
                }
                )", &example);

  Result expected(Failure(Pointer(), "Unexpected member encountered: additionalProperty"));
  ASSERT_EQ(expected, result);
}

TEST(NoAdditionalPropertiesTest,
    GivenAdditionalPropertiesAllowed_WhenParsingAdditionalProperties_ThenSucceeds) {
  AdditionalProperties<AdditionalPropertiesTestObject> example;
  auto result = ParseConfig(R"(
                {
                  "integerValue": 32,
                  "stringValue": "hallo",
                  "additionalProperty": 23
                }
                )", &example);

  ASSERT_TRUE(result.Success());
}

}  // namespace rapidschema
