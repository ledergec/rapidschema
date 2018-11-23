#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "multiple_of_constraint.h"
#include "transform_result_matchers.h"

namespace rapidoson {

    using testing::Test;

    class MultipleOfTest : public Test {
    public:
        MultipleOf<3, int32_t> multiple_of_int;
        MultipleOf<2, double> multiple_of_double;
    };

    TEST_F(MultipleOfTest, GivenMultipleOf_WhenCheckingEqualValue_ThenParsedCorrectly) {
        ASSERT_THAT(multiple_of_int.Check(3), CheckSucceeded());
    }

    TEST_F(MultipleOfTest, GivenMultipleOf_WhenCheckingZeroValue_ThenParsedCorrectly) {
        ASSERT_THAT(multiple_of_int.Check(0), CheckSucceeded());
    }

    TEST_F(MultipleOfTest, GivenMultipleOf_WhenCheckingNoMultipleValue_ThenParsedCorrectly) {
        ASSERT_THAT(multiple_of_int.Check(5), CheckFailed("Expected: MultipleOf 3. Actual: 5"));
    }

    TEST_F(MultipleOfTest, GivenMultipleOfFloat_WhenCheckingNoMultipleValue_ThenParsedCorrectly) {
        ASSERT_THAT(multiple_of_double.Check(2.0), CheckSucceeded());
    }

    TEST_F(MultipleOfTest, GivenMultipleOfDouble_WhenCheckingNoMultipleValue_ThenParsedCorrectly) {
        ASSERT_THAT(multiple_of_double.Check(32.0), CheckSucceeded());
    }

}