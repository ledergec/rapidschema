// Copyright (C) 2019 Christian Ledergerber

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "rapidschema/ostream_operators.h"
#include "rapidschema/schema/object_schema.h"
#include "rapidschema/test_utils.h"

namespace rapidschema {
namespace schema {

using testing::Test;

class ObjectSchemaTest : public Test {
 public:
  ObjectSchema object_;
};

/////////////////////////// Parse DOM Style /////////////////////////////////////////////

TEST_F(ObjectSchemaTest, CanParseSchema) {
  auto result = ParseConfig(R"(
                {
                   "type":"object",
                   "properties":{
                      "property1":{
                        "type":"object"
                      }
                   },
                   "patternProperties":{
                      "patternProperty1.*":{
                        "type":"object"
                      }
                   },
                   "additionalProperties": false,
                   "required":["property1"]
                }
                )", &object_);

  std::cout << result << std::endl;
  ASSERT_TRUE(result.Success());
}

}  // namespace schema
}  // namespace rapidschema
