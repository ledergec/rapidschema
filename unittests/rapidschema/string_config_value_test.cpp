//
// Created by root on 11/25/18.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "rapidschema/configvalue.h"
#include "rapidschema/string_constraints.h"
#include "rapidschema/test_utils.h"
#include "rapidschema/transform_result_matchers.h"

namespace rapidschema {

/////////////////////////// Parse DOM Style /////////////////////////////////////////////

TEST(StringConfigValueTest, WhenParsingDomFloat_ThenFails) {
  auto result = TestLeafType<std::string, float>(23.4);
  ASSERT_THAT(result, TransformFailed("Expected type: std::string. Actual value was: 23.4"));
}

TEST(StringConfigValueTest, WhenParsingDomInt_ThenFails) {
  auto result = TestLeafType<std::string, uint32_t>(23);
  ASSERT_THAT(result, TransformFailed("Expected type: std::string. Actual value was: 23"));
}

TEST(StringConfigValueTest, WhenParsingDomNull_ThenFails) {
  auto result = TestLeafType<std::string, std::nullptr_t>(nullptr);
  ASSERT_THAT(result, TransformFailed("Expected type: std::string. Actual value was: null"));
}

TEST(StringConfigValueTest, WhenParsingDomBool_ThenFails) {
  auto result = TestLeafType<std::string, bool>(false);
  ASSERT_THAT(result, TransformFailed("Expected type: std::string. Actual value was: false"));
}

TEST(StringConfigValueTest, GivenNoConstraints_WhenParsingDomString_ThenSuccess) {
  ConfigValue<std::string> value("leaf");
  auto result = ParseLeaf("ein string", &value);
  ASSERT_THAT(result, TransformSucceeded());
  ASSERT_EQ("ein string", value.Get());
}

/////////////////////////// Validate /////////////////////////////////////////////

TEST(StringConfigValueTest, GivenMinLengthConstraint_WhenValidatingShortString_ThenFails) {
  ConfigValue<std::string, MinLength> value("leaf");
  value.GetConstraint<MinLength>().SetMinLength(20);
  value = "ein string";
  auto result = value.Validate();
  ASSERT_THAT(result,
      TransformFailed("Expected std::string of length at least 20. Actual: length 10 string: \"ein string\""));
}

TEST(StringConfigValueTest, GivenMinLengthConstraintUsingMakeValue_WhenValidatingShortString_ThenFails) {
  auto value = MakeValue("leaf", MinLength(20));
  value.GetConstraint<MinLength>().SetMinLength(20);
  value = "ein string";
  auto result = value.Validate();
  ASSERT_THAT(result,
      TransformFailed("Expected std::string of length at least 20. Actual: length 10 string: \"ein string\""));
}

TEST(StringConfigValueTest, GivenMaxLengthConstraint_WhenValidatingLongString_ThenFails) {
  ConfigValue<std::string, MaxLength> value("leaf");
  value.GetConstraint<MaxLength>().SetMaxLength(2);
  value = "ein string";
  auto result = value.Validate();
  ASSERT_THAT(result,
      TransformFailed("Expected std::string of length at most 2. Actual: length 10 string: \"ein string\""));
}

}  // namespace rapidschema