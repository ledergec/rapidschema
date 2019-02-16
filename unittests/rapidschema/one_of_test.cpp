// Copyright (C) 2019 Christian Ledergerber

#include <tuple>
#include <type_traits>

#include <gtest/gtest.h>

#include "rapidschema/no_additional_properties.h"
#include "rapidschema/object.h"
#include "rapidschema/one_of.h"
#include "rapidschema/range_constraints.h"
#include "rapidschema/test_utils.h"
#include "rapidschema/transform_result_matchers.h"
#include "rapidschema/value.h"

namespace rapidschema {

using testing::Test;

class OneOfIntegerTestObject : public Object {
 public:
  OneOfIntegerTestObject()
      : integer_value(MakeValue(22, Minimum<int>(100))) {}

  Value<int, Minimum> integer_value;

 protected:
  PropertyMapping CreatePropertyMapping() const override {
    return {{"integerValue", &integer_value}};
  }
};

class OneOfStringTestObject : public Object {
 public:
  OneOfStringTestObject()
      : string_value(MakeValue<std::string>("hallo")) {}

  Value<std::string> string_value;

 protected:
  PropertyMapping CreatePropertyMapping() const override {
    return {{"stringValue", &string_value}};
  }
};

class OneOfTest : public Test {
 public:
  OneOf<OneOfIntegerTestObject, OneOfStringTestObject> one_of_;
};

/////////////////////////// Parse DOM Style /////////////////////////////////////////////

TEST_F(OneOfTest, GivenSingleVariantMatches_WhenParsingDom_ThenCorrectlyParsed) {
  auto result = ParseConfig(R"({"integerValue":112})", &one_of_);
  ASSERT_TRUE(result.Success());
  ASSERT_EQ(112, one_of_.GetVariant<OneOfIntegerTestObject>().integer_value.Get());
  ASSERT_TRUE(one_of_.Is<OneOfIntegerTestObject>());
}

TEST_F(OneOfTest, GivenNoVariantMatches_WhenParsingDom_ThenCorrectlyErrorMessages) {
  auto result = ParseConfig(R"({"integerValue":"string"})", &one_of_);
  ASSERT_EQ(3, result.GetFailures().size());
  ASSERT_EQ("No type in OneOf matched for the following 2 reasons:", result.GetFailures()[0].GetMessage());
  ASSERT_EQ("Expected type: int. Actual value was: \"string\"", result.GetFailures()[1].GetMessage());
  ASSERT_EQ("Is missing.", result.GetFailures()[2].GetMessage());
}

TEST_F(OneOfTest, GivenMultipleVariantMatches_WhenParsingDom_ThenCorrectlyErrorMessages) {
  OneOf<OneOfIntegerTestObject, NoAdditionalProperties<OneOfIntegerTestObject>> example;
  auto result = ParseConfig(R"({"integerValue":112})", &example);
  ASSERT_THAT(result, TransformFailed("Multiple matches - ambiguous result.", ""));
}

/////////////////////////// Validate /////////////////////////////////////////////

TEST_F(OneOfTest, GivenOutOfRangeValue_WhenValidating_ThenCorrectlyErrorMessage) {
  one_of_.SelectVariant<OneOfIntegerTestObject>();
  auto result = one_of_.Validate();
  ASSERT_THAT(result, TransformFailed("Expected: >= 100. Actual: 22", "integerValue"));
}

TEST_F(OneOfTest, GivenInRangeValue_WhenValidating_ThenSuccess) {
  one_of_.GetVariant<OneOfIntegerTestObject>().integer_value = 200;
  one_of_.SelectVariant<OneOfIntegerTestObject>();
  auto result = one_of_.Validate();
  ASSERT_TRUE(result.Success());
}

/////////////////////////// Serialization /////////////////////////////////////////////

TEST_F(OneOfTest, WhenSerialized_ThenCorrectVariantSerialized) {
  one_of_.SelectVariant<OneOfIntegerTestObject>();
  std::string result = SerializeConfig(one_of_);
  ASSERT_EQ(R"({"integerValue":22})", result);
  one_of_.SelectVariant<OneOfStringTestObject>();
  result = SerializeConfig(one_of_);
  ASSERT_EQ(R"({"stringValue":"hallo"})", result);
}

}  // namespace rapidschema
