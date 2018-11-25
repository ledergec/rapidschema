#include <gtest/gtest.h>

#include "string_constraints.h"
#include "transform_result_matchers.h"

namespace rapidoson {

    TEST(StringConstraintsTest, GivenShortEnoughString_WhenMaxLengthConstraintChecked_ThenSuccess) {
        MaxLength max_length(3);
        ASSERT_THAT(max_length.Check("mau"), CheckSucceeded());
    }

    TEST(StringConstraintsTest, GivenTooLongString_WhenMaxLengthConstraintChecked_ThenFails) {
        MaxLength max_length(3);
        ASSERT_THAT(max_length.Check("miau"), CheckFailed("Expected std::string of length at most 3. Actual: miau of size 4"));
    }

    TEST(StringConstraintsTest, GivenLongEnoughString_WhenMinLengthConstraintChecked_ThenSuccess) {
        MinLength min_length(3);
        ASSERT_THAT(min_length.Check("mau"), CheckSucceeded());
    }

    TEST(StringConstraintsTest, GivenTooShortString_WhenMinLengthConstraintChecked_ThenFails) {
        MinLength min_length(3);
        ASSERT_THAT(min_length.Check("ma"), CheckFailed("Expected std::string of length at least 3. Actual: ma of size 2"));
    }
}
