#include <gtest/gtest.h>

#include "configvalue.h"
#include "multiple_of_constraint.h"
#include "range_constraints.h"
#include "test_utils.h"

namespace rapidoson {

    TEST(ConfigValueInt32Test, GivenMultipleConstraintsSatisfied_WhenParsingValue_ThenParsedCorrectly) {
        TestLeafConstraints<int32_t, Minimum<int32_t, 3>,
                MultipleOf<6, int32_t>>(12);
    }

    TEST(ConfigValueInt32Test, GivenFirstConstraintNotSatisfied_WhenParsingValue_ThenParsingFails) {
        TestLeafConstraints<int32_t, Minimum<int32_t, 3>,
                MultipleOf<6, int32_t>>(0, false, "Expected: >= 3. Actual: 0");
    }

    TEST(ConfigValueInt32Test, GivenSecondConstraintNotSatisfied_WhenParsingValue_ThenParsingFails) {
        TestLeafConstraints<int32_t, Minimum<int32_t, 3>,
                MultipleOf<6, int32_t>>(10, false, "Expected: MultipleOf 6. Actual: 10");
    }

    TEST(ConfigValueInt32Test, GivenBothConstraintsNotSatisfied_WhenParsingValue_ThenFirstFails) {
        TestLeafConstraints<int32_t, Minimum<int32_t, 1>,
                MultipleOf<6, int32_t>>(0, false, "Expected: >= 1. Actual: 0");
    }

}