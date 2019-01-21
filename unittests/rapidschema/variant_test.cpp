// Copyright (C) 2019 Christian Ledergerber

#include <tuple>
#include <type_traits>

#include <gtest/gtest.h>

#include "rapidschema/object.h"
#include "rapidschema/value.h"
#include "rapidschema/range_constraints.h"
#include "rapidschema/string_constraints.h"
#include "rapidschema/test_utils.h"
#include "rapidschema/transform_result_matchers.h"
#include "rapidschema/variant.h"

namespace rapidschema {

/////////////////////////// Parse DOM Style /////////////////////////////////////////////

TEST(VariantTest, GivenSingleVariantNoConstraints_WhenParsingDomVariant_ThenVariantCanBeParsed) {
  Variant<Value<int32_t>> variant;
  auto result = ParseLeaf<int32_t>(124, &variant);
  ASSERT_THAT(result, TransformSucceeded());
  ASSERT_EQ(124, variant.GetVariant<int32_t>().Get());
}

TEST(VariantTest, GivenWrongJsonType_WhenParsingDomVariant_ThenVariantFails) {
  Variant<Value<int32_t>> variant;
  auto result = ParseLeaf<std::string>("hallo", &variant);
  ASSERT_THAT(result, TransformFailed("No type in variant matched. Actual type: string", ""));
}

TEST(VariantTest, GivenMultipleVariants_WhenParsingDomVariant_ThenCorrectVariantParsed) {
  Variant<Value<int32_t>,
          Value<std::string>> variant;
  auto result = ParseLeaf<std::string>("hallo", &variant);
  ASSERT_THAT(result, TransformSucceeded());
  ASSERT_FALSE(variant.Is<int32_t>());
  ASSERT_TRUE(variant.Is<std::string>());
  ASSERT_EQ("hallo", variant.GetVariant<std::string>().Get());
}

/////////////////////////// Validate /////////////////////////////////////////////

TEST(VariantTest, GivenMultipleVariantsWithConstraints_WhenValdiatingVariant_ThenConstraintsApplied) {
  Variant<Value<int32_t, Minimum>,
          Value<std::string, MaxLength>> variant;
  variant = std::string("hallo");
  ASSERT_TRUE(variant.Is<std::string>());
  ASSERT_EQ("hallo", variant.GetVariant<std::string>().Get());

  auto result = variant.Validate();
  ASSERT_THAT(result, TransformFailed("Expected string of length at most 0. "
                                      "Actual: length 5 string: \"hallo\"", ""));
}

TEST(VariantTest, GivenMultipleVariantsCreatedWithMakeVariant_WhenValidatingVariant_ThenConstraintsApplied) {
  auto variant = MakeVariant(
      MakeVariantValue<int32_t, Minimum>(Minimum<int32_t>(10)),
      MakeVariantValue<std::string, MaxLength>(MaxLength<>(4)));

  variant = std::string("hallo");
  ASSERT_TRUE(variant.Is<std::string>());
  ASSERT_EQ("hallo", variant.GetVariant<std::string>().Get());

  auto result = variant.Validate();
  ASSERT_THAT(result, TransformFailed("Expected string of length at most 4. "
                                      "Actual: length 5 string: \"hallo\"", ""));
}

TEST(VariantTest, GivenMultipleVariantsWithDynamicallySetConstraints_WhenValidatingVariant_ThenConstraintsApplied) {
  Variant<Value<int32_t, Minimum>,
          Value<std::string, MaxLength>> variant;
  variant = std::string("hallo");
  ASSERT_TRUE(variant.Is<std::string>());

  variant.GetVariant<std::string>().GetConstraint<MaxLength>().SetMaxLength(4);

  auto result = variant.Validate();
  ASSERT_THAT(result, TransformFailed("Expected string of length at most 4. "
                                      "Actual: length 5 string: \"hallo\"", ""));
}

/////////////////////////// Serialization /////////////////////////////////////////////

class VariantTestTestNode : public Object {
 public:
  VariantTestTestNode()
    : variant(MakeVariant<Value<int64_t>, Value<std::string>>(
          MakeVariantValue<int64_t>(), MakeVariantValue<std::string>())) {}

  Variant<Value<int64_t>, Value<std::string>> variant;

 protected:
  std::map<std::string, const Config*> CreateMemberMapping() const override {
    return {{"value", &variant}};
  }
};

TEST(VariantTest, WhenSerialize_ThenCorrectResult) {
  VariantTestTestNode node;
  node.variant.SetVariant<std::string>("my_string");
  std::string result = SerializeConfig(node);
  ASSERT_EQ(R"({"value":"my_string"})", result);
  node.variant.SetVariant<int64_t>(123);
  result = SerializeConfig(node);
  ASSERT_EQ(R"({"value":123})", result);
}

}  // namespace rapidschema
