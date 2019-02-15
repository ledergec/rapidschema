// Copyright (C) 2019 Christian Ledergerber

#include <iostream>
#include <map>

#include <rapidschema/array.h>
#include <rapidschema/no_additional_properties.h>
#include <rapidschema/object.h>
#include <rapidschema/range_constraints.h>
#include <rapidschema/string_constraints.h>
#include <rapidschema/value.h>

using namespace rapidschema;  // NOLINT[build/namespaces]

// Definition of the C++ class which will be filled with data from the json
// This class contains additional schema information
class SimpleExample : public NoAdditionalProperties<Object> {
 public:
  Value<int, Minimum> integer_value;
  Value<std::string, MaxLength> string_value;

  SimpleExample()
    : integer_value(MakeValue<int, Minimum>(Minimum<int>(10)))
    , string_value(MakeValue<std::string, MaxLength>(MaxLength<>(20))) {}

 protected:
  // Definition of the mapping from json property names to members of the C++ class
  PropertyMapping CreatePropertyMapping() const override {
    return {{"integerValue", &integer_value},
            {"stringValue", &string_value}};
  }
};

int main() {
  // The object to be filled with data
  SimpleExample simple_example;

  // Json string to be parsed
  std::string json_string =
      R"(
      {
        "integerValue": 5,
        "stringValue": "My dog wears sunglasses!",
        "additionalProperty": [1, 2, 3]
      }
      )";

  // Parsing the json string into the object
  rapidjson::Document document;
  document.Parse(json_string.c_str());
  auto result = simple_example.Transform(document);

  // Reporting the errors
  size_t i = 1;
  for (const auto& failure : result.GetFailures()) {
    std::cout << "Transform Error " << i << " is located at: \"" << failure.GetPath()
              << "\" and the corresponding message is: " << failure.GetMessage() << std::endl;
    i++;
  }

  result = simple_example.Validate();

  // Reporting the errors
  i = 1;
  for (const auto& failure : result.GetFailures()) {
    std::cout << "Validation Error " << i << " is located at \"" << failure.GetPath()
              << "\" and the corresponding message is: " << failure.GetMessage() << std::endl;
    i++;
  }

  return 0;
}

