#include <gtest/gtest.h>

#include "range_constraints.h"
#include "transform_result_matchers.h"

namespace rapidoson {

    TEST(RangeConstraints, GivenMinimum_WhenMinimumConstraintChecked_ThenSuccess) {
        Minimum<int32_t, 3> minimum;
        ASSERT_THAT(minimum.Check(3), CheckSucceeded());
    }

    TEST(RangeConstraints, GivenJustOutOfBounds_WhenMinimumConstraintCheckt_ThenFails) {
        Minimum<int32_t, 3> minimum;
        ASSERT_THAT(minimum.Check(2), CheckFailed("Expected: >= 3. Actual: 2"));
    }

    TEST(RangeConstraints, GivenLargerThanMinimum_WhenExclusiveMinimumConstraintChecked_ThenFails) {
        ExclusiveMinimum<int32_t, 3> exclusive_minimum;
        ASSERT_THAT(exclusive_minimum.Check(4), CheckSucceeded());
    }

    TEST(RangeConstraints, GivenMinimum_WhenExclusiveMinimumConstraintChecked_ThenSuccess) {
        ExclusiveMinimum<int32_t, 3> exclusive_minimum;
        ASSERT_THAT(exclusive_minimum.Check(3), CheckFailed("Expected: > 3. Actual: 3"));
    }

    TEST(RangeConstraints, GivenMaximum_WhenMaximumConstraintChecked_ThenSuccess) {
        Maximum<int32_t, 3> maximum;
        ASSERT_THAT(maximum.Check(3), CheckSucceeded());
    }

    TEST(RangeConstraints, GivenJustOutOfBounds_WhenMaximumConstraintChecked_ThenFails) {
        Maximum<int32_t, 3> maximum;
        ASSERT_THAT(maximum.Check(4), CheckFailed("Expected: <= 3. Actual: 4"));
    }

    TEST(RangeConstraints, GivenLowerThanMaximum_WhenMaximumConstraintChecked_ThenSuccess) {
        ExclusiveMaximum<int32_t, 3> exclusive_maximum;
        ASSERT_THAT(exclusive_maximum.Check(2), CheckSucceeded());
    }

    TEST(RangeConstraints, GivenMaximum_WhenMaximumConstraintChecked_ThenFails) {
        ExclusiveMaximum<int32_t, 3> exclusive_maximum;
        ASSERT_THAT(exclusive_maximum.Check(3), CheckFailed("Expected: < 3. Actual: 3"));
    }
}