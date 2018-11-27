//
// Created by root on 11/26/18.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <chrono>

#include "configvalue.h"
#include "range_constraints.h"
#include "test_utils.h"
#include "transform_result_matchers.h"
#include "type_properties.h"

std::ostream& operator<<(std::ostream& stream, const std::chrono::milliseconds& milliseconds) {
    stream << milliseconds.count() << " [ms]";
}

namespace rapidoson {

    template<>
    struct TypeProperties<std::chrono::milliseconds> {
        static constexpr JsonType json_type = JsonType::NULLTYPE;

        static constexpr char name[] = "nullptr_t";

        static bool IsType(const rapidjson::Value &value) {
            return value.IsUint64();
        }

        static std::chrono::milliseconds FromJson(const rapidjson::Value &value) {
            return std::chrono::milliseconds(value.GetUint64());
        }
    };

    TEST(Int64ConfigValueTest, CanParseCustomType) {
        auto json = R"({"leaf": 123})";
        ConfigValue<std::chrono::milliseconds> value;
        auto result = ParseJsonLeaf(json, &value);
        ASSERT_THAT(result, TransformSucceeded());
        ASSERT_EQ(std::chrono::milliseconds(123), value.Get());
    }

}