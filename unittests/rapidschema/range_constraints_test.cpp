#include <gtest/gtest.h>

#include "rapidschema/range_constraints.h"
#include "rapidschema/transform_result_matchers.h"

namespace rapidschema {

TEST(RangeConstraintsTest, GivenMinimum_WhenMinimumConstraintChecked_ThenSuccess) {
    Minimum<uint32_t> minimum(3);
    ASSERT_THAT(minimum.Check(3), CheckSucceeded());
}

TEST(RangeConstraintsTest, GivenMinimumDouble_WhenMinimumConstraintChecked_ThenSuccess) {
    Minimum<double> minimum(3.0);
    ASSERT_THAT(minimum.Check(3.23), CheckSucceeded());
}

TEST(RangeConstraintsTest, GivenJustOutOfBounds_WhenMinimumConstraintCheckt_ThenFails) {
    Minimum<uint32_t> minimum(3);
    ASSERT_THAT(minimum.Check(2), CheckFailed("Expected: >= 3. Actual: 2"));
}

TEST(RangeConstraintsTest, GivenLargerThanMinimum_WhenExclusiveMinimumConstraintChecked_ThenFails) {
    ExclusiveMinimum<uint32_t> exclusive_minimum(3);
    ASSERT_THAT(exclusive_minimum.Check(4), CheckSucceeded());
}

TEST(RangeConstraintsTest, GivenMinimum_WhenExclusiveMinimumConstraintChecked_ThenSuccess) {
    ExclusiveMinimum<uint32_t> exclusive_minimum(3);
    ASSERT_THAT(exclusive_minimum.Check(3), CheckFailed("Expected: > 3. Actual: 3"));
}

TEST(RangeConstraintsTest, GivenMaximum_WhenMaximumConstraintChecked_ThenSuccess) {
    Maximum<uint32_t> maximum(3);
    ASSERT_THAT(maximum.Check(3), CheckSucceeded());
}

TEST(RangeConstraintsTest, GivenJustOutOfBoundsDouble_WhenMaximumConstraintChecked_ThenFails) {
    Maximum<double> maximum(3.0);
    ASSERT_THAT(maximum.Check(3.21), CheckFailed("Expected: <= 3. Actual: 3.21"));
}

TEST(RangeConstraintsTest, GivenJustOutOfBounds_WhenMaximumConstraintChecked_ThenFails) {
    Maximum<uint32_t> maximum(3);
    ASSERT_THAT(maximum.Check(4), CheckFailed("Expected: <= 3. Actual: 4"));
}

TEST(RangeConstraintsTest, GivenLowerThanMaximum_WhenMaximumConstraintChecked_ThenSuccess) {
    ExclusiveMaximum<uint32_t> exclusive_maximum(3);
    ASSERT_THAT(exclusive_maximum.Check(2), CheckSucceeded());
}

TEST(RangeConstraintsTest, GivenMaximum_WhenMaximumConstraintChecked_ThenFails) {
    ExclusiveMaximum<uint32_t> exclusive_maximum(3);
    ASSERT_THAT(exclusive_maximum.Check(3), CheckFailed("Expected: < 3. Actual: 3"));
}

}  // namespace rapidschema
