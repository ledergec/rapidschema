// Copyright (C) 2019 Christian Ledergerber

#include <iostream>
#include <map>

#include <rapidjson/prettywriter.h>

#include <rapidschema/array.h>
#include <rapidschema/generic_writer.h>
#include <rapidschema/no_additional_properties.h>
#include <rapidschema/object.h>
#include <rapidschema/range_constraints.h>
#include <rapidschema/schema/schema_assembler.h>
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
  schema::SchemaAssembler assembler;

  // The object to be filled with data
  SimpleExample simple_example;
  auto schema = simple_example.CreateSchema(assembler);

  // Serialize the object to json
  rapidjson::StringBuffer buffer;
  rapidschema::GenericWriter<rapidjson::PrettyWriter<rapidjson::StringBuffer>> writer(buffer);
  schema->Serialize(&writer);

  std::cout << buffer.GetString() << std::endl;

  return 0;
}

