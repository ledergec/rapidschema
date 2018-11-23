#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "configvalue.h"
#include "range_constraints.h"
#include "test_utils.h"
#include "transform_result_matchers.h"

namespace rapidoson {

    struct ConfigurableConstraint {
        std::optional<Failure> Check(const float&) const {
            return result;
        }

        std::optional<Failure> result;
    };

    TEST(ConfigurableConstraintTest, WhenConstraintConfigure_CorrectlyValidated) {
        ConfigValue<float, ConfigurableConstraint> value("leaf");
        value.GetConstraint<ConfigurableConstraint>().result = std::nullopt;
        TestValueConstraints<float, ConfigurableConstraint>(&value, 3.0f);

        value.GetConstraint<ConfigurableConstraint>().result = std::optional(Failure("message"));
        auto result = TestValueConstraints<float, ConfigurableConstraint>(&value, 3.0f);
        ASSERT_THAT(result, TransformFailed("message"));
    }

}