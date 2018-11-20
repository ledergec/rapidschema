#include <gtest/gtest.h>

#include "configvalue.h"
#include "int_constraints.h"
#include "string_constraints.h"
#include "test_utils.h"

namespace rapidoson {

    TEST(ConfigValueInt32Test, GivenMinimumConstraint_WhenParsingValueInRange_ThenParsedCorrectly) {
        TestLeafConstraints<int32_t, Minimum<int32_t, 3>>(3);
    }

    TEST(ConfigValueInt32Test, GivenMinimumConstraint_WhenParsingValueOutOfRange_ThenParsingFails) {
        TestLeafConstraints<int32_t, Minimum<int32_t, 3>>(2, false, "Expected: >= 3. Actual: 2");
    }
}