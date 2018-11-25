#include <gtest/gtest.h>

#include "combined_constraint.h"
#include "multiple_of_constraint.h"
#include "range_constraints.h"
#include "transform_result_matchers.h"

namespace rapidoson {

    using testing::Test;
    using testing::UnorderedElementsAre;

    class CombinedConstraintTest : public Test {
    public:
        CombinedConstraintTest()
        : constraint(MakeConstraint(Minimum<uint32_t>(3), MultipleOf<uint32_t >(6))) {}

        CombinedConstraint<uint32_t, Minimum, MultipleOf> constraint;
    };

    TEST_F(CombinedConstraintTest, GivenMultipleConstraintsSatisfied_WhenParsingValue_ThenParsedCorrectly) {
        auto result = constraint.Check(12);
        ASSERT_THAT(result, TransformSucceeded());
    }

    TEST_F(CombinedConstraintTest, GivenFirstConstraintNotSatisfied_WhenParsingValue_ThenParsingFails) {
        auto result = constraint.Check(0);
        ASSERT_THAT(result, TransformFailed("Expected: >= 3. Actual: 0"));
    }

    TEST_F(CombinedConstraintTest, GivenSecondConstraintNotSatisfied_WhenParsingValue_ThenParsingFails) {
        auto result = constraint.Check(10);
        ASSERT_THAT(result, TransformFailed("Expected: MultipleOf 6. Actual: 10"));
    }

    TEST_F(CombinedConstraintTest, GivenBothConstraintsNotSatisfied_WhenParsingValue_ThenBothReported) {
        auto result = constraint.Check(1);
        ASSERT_EQ(2, result.GetFailures().size());
        ASSERT_THAT(result.GetFailures(), UnorderedElementsAre(Failure("Expected: >= 3. Actual: 1"),
                Failure("Expected: MultipleOf 6. Actual: 1")));
    }

}