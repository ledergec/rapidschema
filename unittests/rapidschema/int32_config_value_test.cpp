#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "rapidschema/confignode.h"
#include "rapidschema/configvalue.h"
#include "rapidschema/generic_reader.h"
#include "rapidschema/range_constraints.h"
#include "rapidschema/test_utils.h"
#include "rapidschema/transform_result_matchers.h"

namespace rapidschema {

/////////////////////////// Parse DOM Style /////////////////////////////////////////////

TEST(Int32ConfigValueTest, WhenParsingDomFloat_ThenFails) {
  auto result = TestLeafType<int32_t, float>(23.4);
  ASSERT_THAT(result, TransformFailed("Expected type: int. Actual value was: 23.4"));
}

TEST(Int32ConfigValueTest, WhenParsingDomString_ThenFails) {
  auto result = TestLeafType<int32_t, std::string>("ein string");
  ASSERT_THAT(result, TransformFailed("Expected type: int. Actual value was: \"ein string\""));
}

TEST(Int32ConfigValueTest, WhenParsingDomNull_ThenFails) {
  auto result = TestLeafType<int32_t, std::nullptr_t>(nullptr);
  ASSERT_THAT(result, TransformFailed("Expected type: int. Actual value was: null"));
}

TEST(Int32ConfigValueTest, WhenParsingDomBool_ThenFails) {
  auto result = TestLeafType<int32_t, bool>(false);
  ASSERT_THAT(result, TransformFailed("Expected type: int. Actual value was: false"));
}

TEST(Int32ConfigValueTest, WhenParsingDomOutOfLowerRange_ThenFails) {
  auto out_of_range = static_cast<int64_t>(std::numeric_limits<int32_t>::min()) - 1;
  auto result = TestLeafType<int32_t, int64_t>(out_of_range);
  ASSERT_THAT(result, TransformFailed("Expected type: int. Actual value was: -2147483649"));
}

TEST(Int32ConfigValueTest, WhenParsingDomOutOfUpperRange_ThenFails) {
  auto out_of_range = static_cast<int64_t>(std::numeric_limits<int32_t>::max()) + 1;
  auto result = TestLeafType<int32_t, int64_t>(out_of_range);
  ASSERT_THAT(result, TransformFailed("Expected type: int. Actual value was: 2147483648"));
}

TEST(Int32ConfigValueTest, WhenParsing23_ThenParsedCorrectly) {
  auto result = TestLeafType<int32_t, int32_t>(23);
  ASSERT_THAT(result, TransformSucceeded());
}

TEST(Int32ConfigValueTest, WhenParsingLowerLimit_ThenParsedCorrectly) {
  auto result = TestLeafType<int32_t, int32_t>(std::numeric_limits<int32_t>::min());
  ASSERT_THAT(result, TransformSucceeded());
}

TEST(Int32ConfigValueTest, WhenParsingUpperLimit_ThenParsedCorrectly) {
  auto result = TestLeafType<int32_t, int32_t>(std::numeric_limits<int32_t>::max());
  ASSERT_THAT(result, TransformSucceeded());
}

/////////////////////////// Serialization /////////////////////////////////////////////

class Int32ConfigValueTestNode : public Node {
 public:
  Value<int32_t> value;

 protected:
  std::map<std::string, const Config*> CreateMemberMapping() const override {
    return {{"value", &value}};
  }
};

TEST(Int32ConfigValueTest, WhenSerialize_ThenCorrectResult) {
  Int32ConfigValueTestNode node;
  node.value = 123;
  std::string result = SerializeConfig(node);
  ASSERT_EQ(R"({"value":123})", result);
}

/////////////////////////// Parse SAX Style /////////////////////////////////////////////

TEST(Int32ConfigValueTest, GivenMissingMember_WhenParsingSax_ThenFails) {
  auto json_string = R"({"leaf": 23})";
  rapidjson::StringStream string_stream(json_string);
  GenericReader<rapidjson::Reader, rapidjson::StringStream> reader(&string_stream);

  Int32ConfigValueTestNode test_node;
  auto result = test_node.Parse(&reader);
  ASSERT_THAT(result, TransformFailed("is missing"));
}

TEST(Int32ConfigValueTest, GivenFloat_WhenParsingSax_ThenFails) {
  auto json_string = R"({"value": 23.5})";
  rapidjson::StringStream string_stream(json_string);
  GenericReader<rapidjson::Reader, rapidjson::StringStream> reader(&string_stream);

  Int32ConfigValueTestNode test_node;
  auto result = test_node.Parse(&reader);
  ASSERT_THAT(result, TransformFailed("is missing"));
}

}  // namespace rapidschema
