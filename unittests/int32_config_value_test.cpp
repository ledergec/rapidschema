#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "configvalue.h"
#include "range_constraints.h"
#include "string_constraints.h"
#include "test_utils.h"
#include "transform_result_matchers.h"

namespace rapidoson {

    TEST(ConfigValueTest, WhenParsingFloat_ThenFails) {
        auto result = TestLeafType<int32_t, float>(23.4);
        ASSERT_THAT(result, TransformFailed("Expected type: int32. Actual value was: 23.4"));
    }

    TEST(ConfigValueTest, WhenParsingString_ThenFails) {
        auto result = TestLeafType<int32_t, std::string>("ein string");
        ASSERT_THAT(result, TransformFailed("Expected type: int32. Actual value was: \"ein string\""));
    }

    TEST(ConfigValueTest, WhenParsingNull_ThenFails) {
        auto result = TestLeafType<int32_t, std::nullptr_t>(nullptr);
        ASSERT_THAT(result, TransformFailed("Expected type: int32. Actual value was: null"));
    }

    TEST(ConfigValueTest, WhenParsingBool_ThenFails) {
        auto result = TestLeafType<int32_t, bool>(false);
        ASSERT_THAT(result, TransformFailed("Expected type: int32. Actual value was: false"));
    }

    TEST(ConfigValueTest, WhenParsingOutOfLowerRange_ThenFails) {
        auto out_of_range = static_cast<int64_t>(std::numeric_limits<int32_t>::min()) - 1;
        auto result = TestLeafType<int32_t, int64_t>(out_of_range);
        ASSERT_THAT(result, TransformFailed("Expected type: int32. Actual value was: -2147483649"));
    }

    TEST(ConfigValueTest, WhenParsingOutOfUpperRange_ThenFails) {
        auto out_of_range = static_cast<int64_t>(std::numeric_limits<int32_t>::max()) + 1;
        auto result = TestLeafType<int32_t, int64_t>(out_of_range);
        ASSERT_THAT(result, TransformFailed("Expected type: int32. Actual value was: 2147483648"));
    }

    TEST(ConfigValueTest, GivenNoConstraints_WhenParsing23_ThenParsedCorrectly) {
        auto result = TestLeafConstraints<int32_t>(23);
        ASSERT_THAT(result, TransformSucceeded());
    }

    TEST(ConfigValueTest, GivenNoConstraints_WhenParsingLowerLimit_ThenParsedCorrectly) {
        TestLeafConstraints<int32_t>(std::numeric_limits<int32_t>::min());
    }

    TEST(ConfigValueTest, GivenNoConstraints_WhenParsingUpperLimit_ThenParsedCorrectly) {
        TestLeafConstraints<int32_t>(std::numeric_limits<int32_t>::max());
    }

}