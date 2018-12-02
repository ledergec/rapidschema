
#include <tuple>
#include <type_traits>

#include <gtest/gtest.h>

#include "configvalue.h"
#include "range_constraints.h"
#include "string_constraints.h"
#include "test_utils.h"
#include "transform_result_matchers.h"
#include "variant.h"

namespace rapidoson {

    TEST(VariantTest, GivenSingleVariantNoConstraints_WhenParsingVariant_ThenVariantCanBeParsed) {
        Variant<ConfigValue<int32_t>> variant("variant");
        auto result = ParseLeaf<int32_t>(124, &variant);
        ASSERT_THAT(result, TransformSucceeded());
        ASSERT_EQ(124, variant.GetVariant<int32_t>().Get());
    }

    TEST(VariantTest, GivenWrongJsonType_WhenParsingVariant_ThenVariantFails) {
        Variant<ConfigValue<int32_t>> variant("variant");
        auto result = ParseLeaf<std::string>("hallo", &variant);
        ASSERT_THAT(result, TransformFailed("No type in variant matched. Actual type: string"));
    }

    TEST(VariantTest, GivenMultipleVariants_WhenParsingVariant_ThenCorrectVariantParsed) {
        Variant<ConfigValue<int32_t>,
                ConfigValue<std::string>> variant("variant");
        auto result = ParseLeaf<std::string>("hallo", &variant);
        ASSERT_THAT(result, TransformSucceeded());
        ASSERT_FALSE(variant.Is<int32_t>());
        ASSERT_TRUE(variant.Is<std::string>());
        ASSERT_EQ("hallo", variant.GetVariant<std::string>().Get());
    }

    TEST(VariantTest, GivenMultipleVariantsWithConstraints_WhenParsingVariant_ThenConstraintsApplied) {
        Variant<ConfigValue<int32_t, Minimum>,
                ConfigValue<std::string, MaxLength>> variant("variant");
        auto result = ParseLeaf<std::string>("hallo", &variant);
        ASSERT_THAT(result, TransformSucceeded());
        ASSERT_FALSE(variant.Is<int32_t>());
        ASSERT_TRUE(variant.Is<std::string>());
        ASSERT_EQ("hallo", variant.GetVariant<std::string>().Get());

        variant.GetVariant<std::string>().GetConstraint<MaxLength>().SetMaxLength(4);

        result = variant.Validate();
        ASSERT_THAT(result, TransformFailed("Expected std::string of length at most 4. Actual: length 5 string: \"hallo\""));
    }
}