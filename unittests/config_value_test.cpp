#include <gtest/gtest.h>

#include "configvalue.h"
#include "int_constraints.h"
#include "string_constraints.h"
#include "test_utils.h"

namespace rapidoson {

    TEST(ConfigValueInt32Test, WhenParsingFloat_ThenFails) {
        TestLeafType<int32_t, float>(23.4, false, "Expected type: int32. Actual value was: 23.4");
    }

    TEST(ConfigValueInt32Test, WhenParsingString_ThenFails) {
        TestLeafType<int32_t, std::string>("ein string", false, "Expected type: int32. Actual value was: \"ein string\"");
    }

    TEST(ConfigValueInt32Test, WhenParsingNull_ThenFails) {
        TestLeafType<int32_t, std::nullptr_t>(nullptr, false, "Expected type: int32. Actual value was: null");
    }

    TEST(ConfigValueInt32Test, WhenParsingBool_ThenFails) {
        TestLeafType<int32_t, bool>(false, false, "Expected type: int32. Actual value was: false");
    }

    TEST(ConfigValueInt32Test, WhenParsingOutOfLowerRange_ThenFails) {
        auto out_of_range = static_cast<int64_t>(std::numeric_limits<int32_t>::min()) - 1;
        TestLeafType<int32_t, int64_t>(out_of_range, false, "Expected type: int32. Actual value was: -2147483649");
    }

    TEST(ConfigValueInt32Test, WhenParsingOutOfUpperRange_ThenFails) {
        auto out_of_range = static_cast<int64_t>(std::numeric_limits<int32_t>::max()) + 1;
        TestLeafType<int32_t, int64_t>(out_of_range, false, "Expected type: int32. Actual value was: 2147483648");
    }

    TEST(ConfigValueInt32Test, GivenNoConstraints_WhenParsing23_ThenParsedCorrectly) {
        TestLeafConstraints<int32_t>(23);
    }

    TEST(ConfigValueInt32Test, GivenNoConstraints_WhenParsingLowerLimit_ThenParsedCorrectly) {
        TestLeafConstraints<int32_t>(std::numeric_limits<int32_t>::min());
    }

    TEST(ConfigValueInt32Test, GivenNoConstraints_WhenParsingUpperLimit_ThenParsedCorrectly) {
        TestLeafConstraints<int32_t>(std::numeric_limits<int32_t>::max());
    }

}