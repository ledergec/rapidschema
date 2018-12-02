
#include <tuple>
#include <type_traits>

#include <gtest/gtest.h>

#include "configvalue.h"
#include "range_constraints.h"
#include "string_constraints.h"
#include "test_utils.h"
#include "transform_result_matchers.h"
#include "variant.h"

namespace rapidschema {

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

    TEST(VariantTest, GivenMultipleVariantsWithConstraints_WhenValdiatingVariant_ThenConstraintsApplied) {
        Variant<ConfigValue<int32_t, Minimum>,
                ConfigValue<std::string, MaxLength>> variant("variant");
        auto result = ParseLeaf<std::string>("hallo", &variant);
        ASSERT_THAT(result, TransformSucceeded());
        ASSERT_TRUE(variant.Is<std::string>());

        result = variant.Validate();
        ASSERT_THAT(result, TransformFailed("Expected std::string of length at most 0. Actual: length 5 string: \"hallo\""));
    }

    TEST(VariantTest, GivenMultipleVariantsWithDynamicallySetConstraints_WhenValidatingVariant_ThenConstraintsApplied) {
        Variant<ConfigValue<int32_t, Minimum>,
                ConfigValue<std::string, MaxLength>> variant("variant");
        auto result = ParseLeaf<std::string>("hallo", &variant);
        ASSERT_THAT(result, TransformSucceeded());
        ASSERT_TRUE(variant.Is<std::string>());

        variant.GetVariant<std::string>().GetConstraint<MaxLength>().SetMaxLength(4);

        result = variant.Validate();
        ASSERT_THAT(result, TransformFailed("Expected std::string of length at most 4. Actual: length 5 string: \"hallo\""));
    }


    TEST(VariantTest, WhenParsingVariantWithCreatedWithMakeVariant_ThenConstraintsApplied) {
        auto variant = MakeVariant(
                "variant",
                MakeVariantValue<int32_t, Minimum>(Minimum(10)),
                MakeVariantValue<std::string, MaxLength>(MaxLength(4)));

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