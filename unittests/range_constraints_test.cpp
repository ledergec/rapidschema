#include <gtest/gtest.h>

#include "configvalue.h"
#include "range_constraints.h"
#include "string_constraints.h"
#include "test_utils.h"

namespace rapidoson {

    TEST(ConfigValueInt32Test, GivenMinimumConstraint_WhenParsingValueInRange_ThenParsedCorrectly) {
        TestLeafConstraints<int32_t, Minimum<int32_t, 3>>(3);
    }

    TEST(ConfigValueInt32Test, GivenMinimumConstraint_WhenParsingValueOutOfRange_ThenParsingFails) {
        TestLeafConstraints<int32_t, Minimum<int32_t, 3>>(2, false, "Expected: >= 3. Actual: 2");
    }

    TEST(ConfigValueInt32Test, GivenExclusiveMinimumConstraint_WhenParsingValueInRange_ThenParsedCorrectly) {
        TestLeafConstraints<int32_t, ExclusiveMinimum<int32_t, 3>>(4);
    }

    TEST(ConfigValueInt32Test, GivenExclusiveMinimumConstraint_WhenParsingValueOutOfRange_ThenParsingFails) {
        TestLeafConstraints<int32_t, ExclusiveMinimum<int32_t, 3>>(3, false, "Expected: > 3. Actual: 3");
    }

    TEST(ConfigValueInt32Test, GivenMaximumConstraint_WhenParsingValueInRange_ThenParsedCorrectly) {
        TestLeafConstraints<int32_t, Maximum<int32_t, 3>>(3);
    }

    TEST(ConfigValueInt32Test, GivenMaximumConstraint_WhenParsingValueOutOfRange_ThenParsingFails) {
        TestLeafConstraints<int32_t, Maximum<int32_t, 3>>(4, false, "Expected: <= 3. Actual: 4");
    }

    TEST(ConfigValueInt32Test, GivenExclusiveMaximumConstraint_WhenParsingValueInRange_ThenParsedCorrectly) {
        TestLeafConstraints<int32_t, ExclusiveMaximum<int32_t, 3>>(2);
    }

    TEST(ConfigValueInt32Test, GivenExclusiveMaximumConstraint_WhenParsingValueOutOfRange_ThenParsingFails) {
        TestLeafConstraints<int32_t, ExclusiveMaximum<int32_t, 3>>(3, false, "Expected: < 3. Actual: 3");
    }
}