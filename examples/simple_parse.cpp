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
  MemberMapping CreateMemberMapping() const override {
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
        "integerValue": 13,
        "stringValue": "Hello World!",
        "intArray": [1, 2, 3]
      }
      )";

  // Parsing the json string into the object
  rapidjson::Document document;
  document.Parse(json_string.c_str());
  simple_example.Transform(document);

  // Writing the contents of the object to std out. Most elements simply convert to basic types.
  std::cout << "integer_value = " << simple_example.integer_value << std::endl;
  std::cout << "string_value = " << simple_example.string_value.Get() << std::endl;
  std::cout << "int_array = [" << simple_example.int_array[0] << ", " << simple_example.int_array[1] << ", " <<
          simple_example.int_array[2] << "]" << std::endl;

  return 0;
}
