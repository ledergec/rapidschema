// Copyright (C) 2019 Christian Ledergerber

#include <iostream>
#include <map>

#include <rapidjson/document.h>

#include <rapidschema/array.h>
#include <rapidschema/object.h>
#include <rapidschema/value.h>

using namespace rapidschema;  // NOLINT[build/namespaces]

// Definition of the C++ class which will be filled with data from the json
class SimpleExample : public Object {
 public:
  Value<int> integer_value;
  Value<std::string> string_value;
  Array<Value<int>> int_array;

 protected:
  // Definition of the mapping from json property names to members of the C++ class
  std::vector<std::pair<std::string, const Config*>> CreateMemberMapping() const override {
    return {{"integerValue", &integer_value},
            {"stringValue", &string_value},
            {"intArray", &int_array}};
  }
};

int main() {
  // The object to be filled with data
  SimpleExample simple_example;

  // Json string to be parsed
  std::string json_string =
      R"(
      {
        "integerValue": 43.3,
        "stringValue": "Hello World!",
        "intArray": [1, 2, 3, null]
      }
      )";

  // Parsing the json string into the object
  rapidjson::Document document;
  document.Parse(json_string.c_str());
  auto result = simple_example.Transform(document);

  // Reporting the errors
  size_t i = 1;
  for (const auto & failure : result.GetFailures()) {
    std::cout << "Error " << i << " is located at " << failure.GetPath() << " and the corresponding message is: "
              << failure.GetMessage() << std::endl;
    i++;
  }

  return 0;
}
