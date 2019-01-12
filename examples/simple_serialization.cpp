// Copyright (C) 2019 Christian Ledergerber

#include <iostream>
#include <map>

#include <rapidjson/prettywriter.h>

#include <rapidschema/array.h>
#include <rapidschema/generic_writer.h>
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
  std::map<std::string, const Config*> CreateMemberMapping() const override {
    return {{"integerValue", &integer_value},
            {"stringValue", &string_value},
            {"intArray", &int_array}};
  }
};

int main() {
  // The object to be filled with data
  SimpleExample simple_example;

  // Fill the object with data
  simple_example.integer_value = 43;
  simple_example.string_value = "My dog wears sunglasses!";
  simple_example.int_array.push_back(123);
  simple_example.int_array.push_back(432);
  simple_example.int_array.push_back(543);

  // Serialize the object to json
  rapidjson::StringBuffer buffer;
  rapidschema::GenericWriter<rapidjson::PrettyWriter<rapidjson::StringBuffer>> writer(buffer);
  simple_example.Serialize(&writer);

  std::cout << buffer.GetString() << std::endl;

  return 0;
}
