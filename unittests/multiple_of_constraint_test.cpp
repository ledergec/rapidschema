#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "multiple_of_constraint.h"
#include "transform_result_matchers.h"

namespace rapidschema {

    using testing::Test;

    class MultipleOfTest : public Test {
    public:
        MultipleOfTest()
        : multiple_of_int(3)
        , multiple_of_double(2.0) {}

        MultipleOf<int32_t> multiple_of_int;
        MultipleOf<double> multiple_of_double;
    };

    TEST_F(MultipleOfTest, GivenMultipleOf_WhenCheckingEqualValue_ThenParsedCorrectly) {
        ASSERT_THAT(multiple_of_int.Check(3), CheckSucceeded());
    }

    TEST_F(MultipleOfTest, GivenMultipleOf_WhenCheckingZeroValue_ThenParsedCorrectly) {
        ASSERT_THAT(multiple_of_int.Check(0), CheckSucceeded());
    }

    TEST_F(MultipleOfTest, GivenNoMultipleOf_WhenCheckingMultipleValue_ThenParsedCorrectly) {
        auto result = multiple_of_int.Check(5);
        ASSERT_THAT(result, CheckFailed("Expected: MultipleOf 3. Actual: 5"));
    }

    TEST_F(MultipleOfTest, GivenMultipleOfFloat_WhenCheckingNoMultipleValue_ThenParsedCorrectly) {
        ASSERT_THAT(multiple_of_double.Check(2.0), CheckSucceeded());
    }

    TEST_F(MultipleOfTest, GivenMultipleOfDouble_WhenCheckingNoMultipleValue_ThenParsedCorrectly) {
        ASSERT_THAT(multiple_of_double.Check(32.0), CheckSucceeded());
    }

}