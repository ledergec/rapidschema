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
                   "type": "object",
                   "properties": {
                      "integerProperty": {
                        "type": "integer",
                        "minimum": 10,
                        "maximum": 20,
                        "exclusiveMinimum": 5,
                        "exclusiveMaximum": 30
                      },
                      "numberProperty": {
                        "type":"number",
                        "minimum": 10.0,
                        "maximum": 20.0,
                        "exclusiveMinimum": 5.0,
                        "exclusiveMaximum": 30.0
                      },
                      "stringProperty": {
                        "type": "string",
                        "minLength": 10,
                        "maxLength": 20
                      },
                      "constStringProperty": {
                        "const": "constant string value"
                      },
                      "constIntegerProperty": {
                        "const": 1
                      },
                      "constNumberProperty": {
                        "const": 1.0
                      },
                      "oneOfProperty": {
                        "oneOf": [
                          { "type": "number", "multipleOf": 5.0 },
                          { "type": "number", "multipleOf": 3.0 }
                        ]
                      }
                   },
                   "patternProperties": {
                      "patternProperty1.*": {
                        "type": "object"
                      }
                   },
                   "additionalProperties": false,
                   "required": ["property1"]
                }
                )", &object_);

  std::cout << result << std::endl;
  ASSERT_TRUE(result.Success());
}

}  // namespace schema
}  // namespace rapidschema
