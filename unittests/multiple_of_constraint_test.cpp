#include <gtest/gtest.h>

#include "configvalue.h"
#include "int_constraints.h"
#include "string_constraints.h"
#include "test_utils.h"

namespace rapidoson {

    TEST(MultipleOfTest, GivenMultipleOf_WhenParsingEqualValue_ThenParsedCorrectly) {
        TestLeafConstraints<int32_t, MultipleOf<3, int32_t>>(3);
    }

    TEST(MultipleOfTest, GivenMultipleOf_WhenParsingZeroValue_ThenParsedCorrectly) {
        TestLeafConstraints<int32_t, MultipleOf<3, int32_t>>(0);
    }

    TEST(MultipleOfTest, GivenMultipleOf_WhenParsingNoMultipleValue_ThenParsedCorrectly) {
        TestLeafConstraints<int32_t, MultipleOf<3, int32_t>>(5, false, "Expected: MultipleOf 3. Actual: 5");
    }

//    TEST(MultipleOfTest, GivenMultipleOfFloat_WhenParsingNoMultipleValue_ThenParsedCorrectly) {
//        TestLeafConstraints<float, MultipleOf<2, float>>(2.0);
//    }
//
//    TEST(MultipleOfTest, GivenMultipleOfDouble_WhenParsingNoMultipleValue_ThenParsedCorrectly) {
//        TestLeafConstraints<double, MultipleOf<2, double>>(32.0);
//    }

}