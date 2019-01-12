// Copyright (C) 2019 Christian Ledergerber

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "rapidschema/value.h"
#include "rapidschema/object.h"
#include "rapidschema/array.h"
#include "rapidschema/test_utils.h"
#include "rapidschema/transform_result_matchers.h"

namespace rapidschema {

using testing::Test;
using testing::UnorderedElementsAre;

class ArrayTestDummyObject : public Object {
 public:
  Value<int> integer_value;

 protected:
  std::map<std::string, const Config*> CreateMemberMapping() const override {
    return {{"integerValue", &integer_value}};
  }
};

class ArrayTest : public Test {
 public:
  Array<Value<double>> double_array_;
  Array<ArrayTestDummyObject> object_array_;
};

/////////////////////////// Parse DOM Style /////////////////////////////////////////////

TEST_F(ArrayTest, GivenSuccess_WhenParsingDoubleArray_ThenAllMembersCorrectlySet) {
  auto result = ParseConfig("[1, 2, 3, 4]", &double_array_);
  ASSERT_THAT(result, TransformSucceeded());
  ASSERT_EQ(1.0, double_array_[0].Get());
  ASSERT_EQ(2.0, double_array_[1].Get());
  ASSERT_EQ(3.0, double_array_[2].Get());
  ASSERT_EQ(4.0, double_array_[3].Get());
}

TEST_F(ArrayTest, GivenSuccess_WhenParsingObjectArray_ThenAllMembersCorrectlySet) {
  auto result = ParseConfig(R"([{"integerValue": 1}, {"integerValue": 2}, {"integerValue": 3}])", &object_array_);
  ASSERT_THAT(result, TransformSucceeded());
  ASSERT_EQ(1, object_array_[0].integer_value.Get());
  ASSERT_EQ(2, object_array_[1].integer_value.Get());
  ASSERT_EQ(3, object_array_[2].integer_value.Get());
}

TEST_F(ArrayTest, GivenIncorrectType_WhenParsingDoubleArray_ThenFails) {
  auto result = ParseConfig(R"([1, 2, 3, "4"])", &double_array_);
  ASSERT_THAT(result, TransformFailed("Expected type: double. Actual value was: \"4\"", "[3]"));
}

TEST_F(ArrayTest, GivenIncorrectType_WhenParsingObjectArray_ThenFails) {
  auto result = ParseConfig(R"([{"integerValue": 1}, {"integerValue": 2}, {"integerValue": "3"}])", &object_array_);
  ASSERT_THAT(result, TransformFailed("Expected type: int. Actual value was: \"3\"", "[2].integerValue"));
}

/////////////////////////// Serialization /////////////////////////////////////////////

TEST_F(ArrayTest, WhenSerializingDoubleArray_ThenCorrectResult) {
  Value<double> tmp;
  tmp = 1.0;
  double_array_.push_back(tmp);
  tmp = 2.0;
  double_array_.push_back(tmp);

  std::string result = SerializeConfig(double_array_);
  ASSERT_EQ(R"([1.0,2.0])", result);
}

TEST_F(ArrayTest, WhenSerializingObjectArray_ThenCorrectResult) {
  ArrayTestDummyObject tmp;
  tmp.integer_value = 1;
  object_array_.push_back(tmp);
  tmp.integer_value = 2;
  object_array_.push_back(tmp);

  std::string result = SerializeConfig(object_array_);
  ASSERT_EQ(R"([{"integerValue":1},{"integerValue":2}])", result);
}

/////////////////////////// Parse SAX Style /////////////////////////////////////////////

// TODO(cledergerber)


}  // namespace rapidschema
