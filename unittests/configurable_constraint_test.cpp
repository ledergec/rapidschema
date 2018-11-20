#include <gtest/gtest.h>

#include "configvalue.h"
#include "range_constraints.h"
#include "string_constraints.h"
#include "test_utils.h"

namespace rapidoson {

    struct ConfigurableConstraint {
        ConfigurableConstraint()
            : result(TransformResult::TRUE()) {}

        TransformResult Check(const float&) const {
            return result;
        }

        TransformResult result;
    };

    TEST(ConfigurableConstraintTest, WhenConstraintConfigure_CorrectlyValidated) {
        ConfigValue<float, ConfigurableConstraint> value("leaf");
        value.GetConstraint<ConfigurableConstraint>().result = TransformResult::TRUE();
        TestValueConstraints<float, ConfigurableConstraint>(&value, 3.0f);

        value.GetConstraint<ConfigurableConstraint>().result = TransformResult(false, "", "message");
        TestValueConstraints<float, ConfigurableConstraint>(&value, 3.0f, false, "message");
    }

}