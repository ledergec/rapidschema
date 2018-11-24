#include <gtest/gtest.h>

#include "string_constraints.h"
#include "transform_result_matchers.h"

namespace rapidoson {

    TEST(StringConstraintsTest, GivenShortEnoughString_WhenMaxLengthConstraintChecked_ThenSuccess) {
        MaxLength<3> max_length;
        ASSERT_THAT(max_length.Check("mau"), CheckSucceeded());
    }

    TEST(StringConstraintsTest, GivenTooLongString_WhenMaxLengthConstraintChecked_ThenFails) {
        MaxLength<3> max_length;
        ASSERT_THAT(max_length.Check("miau"), CheckFailed("Expected std::string of length at most 3. Actual: miau of size 4"));
    }

    TEST(StringConstraintsTest, GivenLongEnoughString_WhenMinLengthConstraintChecked_ThenSuccess) {
        MinLength<3> min_length;
        ASSERT_THAT(min_length.Check("mau"), CheckSucceeded());
    }

    TEST(StringConstraintsTest, GivenTooShortString_WhenMinLengthConstraintChecked_ThenFails) {
        MinLength<3> min_length;
        ASSERT_THAT(min_length.Check("ma"), CheckFailed("Expected std::string of length at least 3. Actual: ma of size 2"));
    }
}
