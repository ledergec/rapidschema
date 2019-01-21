// Copyright (C) 2019 Christian Ledergerber

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <chrono>  // NOLINT(build/c++11)

#include "rapidschema/value.h"
#include "rapidschema/test_utils.h"
#include "rapidschema/transform_result_matchers.h"
#include "rapidschema/type_properties.h"

std::ostream& operator<<(std::ostream& stream, const std::chrono::milliseconds& milliseconds) {
  stream << milliseconds.count() << " [ms]";
  return stream;
}

namespace rapidschema {

template<>
struct TypeProperties<std::chrono::milliseconds> {
  static std::string GetName() {
    return "milliseconds";
  }

  static bool IsType(const rapidjson::Value &value) {
    return value.IsUint64();
  }

  static std::chrono::milliseconds FromJson(const rapidjson::Value &value) {
    return std::chrono::milliseconds(value.GetUint64());
  }

  template <typename TargetCh>
  static void Serialize(const std::chrono::milliseconds& milli, AbstractWriter<TargetCh> * writer) {
    writer->Int64(milli.count());
  }
};

TEST(Int64ConfigValueTest, CanParseCustomType) {
  auto json = R"({"leaf": 123})";
  Value<std::chrono::milliseconds> value;
  auto result = ParseJsonLeaf(json, &value);
  ASSERT_THAT(result, TransformSucceeded());
  ASSERT_EQ(std::chrono::milliseconds(123), value.Get());
}

}  // namespace rapidschema
