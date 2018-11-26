#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "configvalue.h"
#include "range_constraints.h"
#include "test_utils.h"
#include "transform_result_matchers.h"

namespace rapidoson {

    TEST(Int64ConfigValueTest, WhenParsingFloat_ThenFails) {
        auto result = TestLeafType<int64_t, float>(23.4);
        ASSERT_THAT(result, TransformFailed("Expected type: int64. Actual value was: 23.4"));
    }

    TEST(Int64ConfigValueTest, WhenParsingString_ThenFails) {
        auto result = TestLeafType<int64_t, std::string>("ein string");
        ASSERT_THAT(result, TransformFailed("Expected type: int64. Actual value was: \"ein string\""));
    }

    TEST(Int64ConfigValueTest, WhenParsingNull_ThenFails) {
        auto result = TestLeafType<int64_t, std::nullptr_t>(nullptr);
        ASSERT_THAT(result, TransformFailed("Expected type: int64. Actual value was: null"));
    }

    TEST(Int64ConfigValueTest, WhenParsingBool_ThenFails) {
        auto result = TestLeafType<int64_t, bool>(false);
        ASSERT_THAT(result, TransformFailed("Expected type: int64. Actual value was: false"));
    }

    TEST(Int64ConfigValueTest, WhenParsingOutOfLowerRange_ThenFails) {
        auto json = R"({"leaf": -9223372036854775809})";
        ConfigValue<int64_t> value;
        auto result = ParseJsonLeaf(json, &value);
        ASSERT_FALSE(result.Success());
    }

    TEST(Int64ConfigValueTest, WhenParsingLowerRange_ThenSucceeds) {
        auto json = R"({"leaf": -9223372036854775807})";
        ConfigValue<int64_t> value;
        auto result = ParseJsonLeaf(json, &value);
        ASSERT_THAT(result, TransformSucceeded());
    }

    TEST(Int64ConfigValueTest, WhenParsingOutOfUpperRange_ThenFails) {
        auto json = R"({"leaf": 9223372036854775808})";
        ConfigValue<int64_t> value;
        auto result = ParseJsonLeaf(json, &value);
        ASSERT_FALSE(result.Success());
    }

    TEST(Int64ConfigValueTest, WhenParsingUpperRange_ThenSucceeds) {
        auto json = R"({"leaf": 9223372036854775806})";
        ConfigValue<int64_t> value;
        auto result = ParseJsonLeaf(json, &value);
        ASSERT_THAT(result, TransformSucceeded());
    }

    TEST(Int64ConfigValueTest, GivenNoConstraints_WhenParsing23_ThenParsedCorrectly) {
        ConfigValue<int64_t> value;
        auto result = ValidateLeaf<int64_t>(23, &value);
        ASSERT_THAT(result, TransformSucceeded());
    }

    TEST(Int64ConfigValueTest, GivenNoConstraints_WhenParsingLowerLimit_ThenParsedCorrectly) {
        ConfigValue<int64_t> value;
        auto result = ValidateLeaf<int64_t>(std::numeric_limits<int64_t>::min(), &value);
        ASSERT_THAT(result, TransformSucceeded());
    }

    TEST(Int64ConfigValueTest, GivenNoConstraints_WhenParsingUpperLimit_ThenParsedCorrectly) {
        ConfigValue<int64_t> value;
        auto result = ValidateLeaf<int64_t>(std::numeric_limits<int64_t>::max(), &value);
        ASSERT_THAT(result, TransformSucceeded());
    }

}