#include <gtest/gtest.h>

#include "multiple_of_constraint.h"

namespace rapidoson {

    TEST(MultipleOfTest, GivenMultipleOf_WhenCheckingEqualValue_ThenParsedCorrectly) {
        MultipleOf<3, int32_t> multiple_of;
        ASSERT_TRUE(multiple_of.Check(3).Success());
    }

    TEST(MultipleOfTest, GivenMultipleOf_WhenCheckingZeroValue_ThenParsedCorrectly) {
        MultipleOf<3, int32_t> multiple_of;
        ASSERT_TRUE(multiple_of.Check(0).Success());
    }

    TEST(MultipleOfTest, GivenMultipleOf_WhenCheckingNoMultipleValue_ThenParsedCorrectly) {
        MultipleOf<3, int32_t> multiple_of;
        ASSERT_FALSE(multiple_of.Check(5).Success());
        ASSERT_EQ(multiple_of.Check(5).GetMessage(), "Expected: MultipleOf 3. Actual: 5");
    }

    TEST(MultipleOfTest, GivenMultipleOfFloat_WhenCheckingNoMultipleValue_ThenParsedCorrectly) {
        MultipleOf<2, float> multiple_of;
        ASSERT_TRUE(multiple_of.Check(2.0).Success());
    }

    TEST(MultipleOfTest, GivenMultipleOfDouble_WhenCheckingNoMultipleValue_ThenParsedCorrectly) {
        MultipleOf<2, double> multiple_of;
        ASSERT_TRUE(multiple_of.Check(32.0).Success());
    }

}