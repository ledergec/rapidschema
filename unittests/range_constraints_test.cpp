#include <gtest/gtest.h>

#include "range_constraints.h"

namespace rapidoson {

    TEST(ConfigValueInt32Test, GivenMinimumConstraint_WhenParsingValueInRange_ThenParsedCorrectly) {
        Minimum<int32_t, 3> minimum;
        ASSERT_TRUE(minimum.Check(3).Success());
    }

    TEST(ConfigValueInt32Test, GivenMinimumConstraint_WhenParsingValueOutOfRange_ThenParsingFails) {
        Minimum<int32_t, 3> minimum;
        ASSERT_FALSE(minimum.Check(2).Success());
        ASSERT_EQ(minimum.Check(2).GetMessage(), "Expected: >= 3. Actual: 2");
    }

    TEST(ConfigValueInt32Test, GivenExclusiveMinimumConstraint_WhenParsingValueInRange_ThenParsedCorrectly) {
        ExclusiveMinimum<int32_t, 3> exclusive_minimum;
        ASSERT_TRUE(exclusive_minimum.Check(4).Success());
    }

    TEST(ConfigValueInt32Test, GivenExclusiveMinimumConstraint_WhenParsingValueOutOfRange_ThenParsingFails) {
        ExclusiveMinimum<int32_t, 3> exclusive_minimum;
        ASSERT_FALSE(exclusive_minimum.Check(3).Success());
        ASSERT_EQ(exclusive_minimum.Check(3).GetMessage(), "Expected: > 3. Actual: 3");
    }

    TEST(ConfigValueInt32Test, GivenMaximumConstraint_WhenParsingValueInRange_ThenParsedCorrectly) {
        Maximum<int32_t, 3> maximum;
        ASSERT_TRUE(maximum.Check(3).Success());
    }

    TEST(ConfigValueInt32Test, GivenMaximumConstraint_WhenParsingValueOutOfRange_ThenParsingFails) {
        Maximum<int32_t, 3> maximum;
        ASSERT_FALSE(maximum.Check(4).Success());
        ASSERT_EQ(maximum.Check(4).GetMessage(), "Expected: <= 3. Actual: 4");
    }

    TEST(ConfigValueInt32Test, GivenExclusiveMaximumConstraint_WhenParsingValueInRange_ThenParsedCorrectly) {
        ExclusiveMaximum<int32_t, 3> exclusive_maximum;
        ASSERT_TRUE(exclusive_maximum.Check(2).Success());
    }

    TEST(ConfigValueInt32Test, GivenExclusiveMaximumConstraint_WhenParsingValueOutOfRange_ThenParsingFails) {
        Maximum<int32_t, 3> maximum;
        ASSERT_FALSE(maximum.Check(3).Success());
        ASSERT_EQ(maximum.Check(3).GetMessage(), "Expected: < 3. Actual: 3");
    }
}