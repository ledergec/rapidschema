#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "configvalue.h"
#include "range_constraints.h"
#include "test_utils.h"
#include "transform_result_matchers.h"

namespace rapidschema {

    TEST(Int32ConfigValueTest, WhenParsingFloat_ThenFails) {
        auto result = TestLeafType<int32_t, float>(23.4);
        ASSERT_THAT(result, TransformFailed("Expected type: int. Actual value was: 23.4"));
    }

    TEST(Int32ConfigValueTest, WhenParsingString_ThenFails) {
        auto result = TestLeafType<int32_t, std::string>("ein string");
        ASSERT_THAT(result, TransformFailed("Expected type: int. Actual value was: \"ein string\""));
    }

    TEST(Int32ConfigValueTest, WhenParsingNull_ThenFails) {
        auto result = TestLeafType<int32_t, std::nullptr_t>(nullptr);
        ASSERT_THAT(result, TransformFailed("Expected type: int. Actual value was: null"));
    }

    TEST(Int32ConfigValueTest, WhenParsingBool_ThenFails) {
        auto result = TestLeafType<int32_t, bool>(false);
        ASSERT_THAT(result, TransformFailed("Expected type: int. Actual value was: false"));
    }

    TEST(Int32ConfigValueTest, WhenParsingOutOfLowerRange_ThenFails) {
        auto out_of_range = static_cast<int64_t>(std::numeric_limits<int32_t>::min()) - 1;
        auto result = TestLeafType<int32_t, int64_t>(out_of_range);
        ASSERT_THAT(result, TransformFailed("Expected type: int. Actual value was: -2147483649"));
    }

    TEST(Int32ConfigValueTest, WhenParsingOutOfUpperRange_ThenFails) {
        auto out_of_range = static_cast<int64_t>(std::numeric_limits<int32_t>::max()) + 1;
        auto result = TestLeafType<int32_t, int64_t>(out_of_range);
        ASSERT_THAT(result, TransformFailed("Expected type: int. Actual value was: 2147483648"));
    }

    TEST(Int32ConfigValueTest, GivenNoConstraints_WhenParsing23_ThenParsedCorrectly) {
        ConfigValue<int32_t> value;
        auto result = ValidateLeaf<int32_t>(23, &value);
        ASSERT_THAT(result, TransformSucceeded());
    }

    TEST(Int32ConfigValueTest, GivenNoConstraints_WhenParsingLowerLimit_ThenParsedCorrectly) {
        ConfigValue<int32_t> value;
        auto result = ValidateLeaf<int32_t>(std::numeric_limits<int32_t>::min(), &value);
        ASSERT_THAT(result, TransformSucceeded());
    }

    TEST(Int32ConfigValueTest, GivenNoConstraints_WhenParsingUpperLimit_ThenParsedCorrectly) {
        ConfigValue<int32_t> value;
        auto result = ValidateLeaf<int32_t>(std::numeric_limits<int32_t>::max(), &value);
        ASSERT_THAT(result, TransformSucceeded());
    }

}