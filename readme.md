## Parsing and Validating the Structure of Json Data with a Breeze

There are a number of json parsers for C / C++. They give the user access to the underlying json structure. Rapidschema
tries to lift the level of abstraction. It transforms the json data directly into C++ classes which give easy access to
the parsed information. For java for instance, there exist such libraries, one example is 
[gson](https://github.com/google/gson). Rapidschema does not quite match the ease of use of gson from a users 
perspective, but gets close.

### Parsing

Consider the following simple example:

~~~~~~~~~~cpp
//file: examples/simple_parse.cpp
#include <iostream>
#include <map>

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
  PropertyMapping CreatePropertyMapping() const override {
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
~~~~~~~~~~

When run the output will be:

~~~~~~~~~~shell
integer_value = 13
string_value = Hello World!
int_array = [1, 2, 3]
~~~~~~~~~~

It shows how to parse a json string into a C++ class. The only significant difference to gson is
that we need to explicitly provide the information, which member has which json property name, in the 
CreatePropertyMapping function. This is not necessary in gson because gson uses java reflection to infer the json 
property names based on the names of the members in the java struct.

### Error Handling - Best Effort Parsing

What if a given member is not present in the json string, the string does not have a valid json syntax or one of the 
properties in the json string has an unexpected type?

Rapidschema does a best effort parse. That is, it will not stop parsing after encountering the first error, but will
try to continue. When done with parsing, rapidschema reports a ParseResult. This contains a list of all
identified problems with the json string. See the example below:

~~~~~~~~~~cpp
//file: examples/simple_error.cpp
#include <iostream>
#include <map>

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
  PropertyMapping CreatePropertyMapping() const override {
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
~~~~~~~~~~

When run the output will be:

~~~~~~~~~~shell
Error 1 is located at intArray[3] and the corresponding message is: Expected type: int. Actual value was: null
Error 2 is located at integerValue and the corresponding message is: Expected type: int. Actual value was: 43.3
~~~~~~~~~~

You can decide how to log or report the encountered errors yourself. Especially in large config files knowing where 
exactly the config file has a defect can save you some grieve hours.

### Serialization

It is also quite easy to assemble an object in C++ and then serialize it to a json string. See the following example:

~~~~~~~~~~cpp
//file: examples/simple_serialization.cpp
#include <iostream>
#include <map>

#include <rapidjson/prettywriter.h>

#include <rapidschema/array.h>
#include <rapidschema/generic_writer.h>
#include <rapidschema/object.h>
#include <rapidschema/value.h>

using namespace rapidschema;  // NOLINT[build/namespaces]

// Definition of the C++ class which will be filled with data and then serialized to json
class SimpleExample : public Object {
 public:
  Value<int> integer_value;
  Value<std::string> string_value;
  Array<Value<int>> int_array;

 protected:
  // Definition of the mapping from json property names to members of the C++ class
  PropertyMapping CreatePropertyMapping() const override {
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
~~~~~~~~~~

Which will output the following json string:

~~~~~~~~~~json
{
    "intArray": [
        543,
        0,
        0
    ],
    "integerValue": 43,
    "stringValue": "My dog wears sunglasses!"
}
~~~~~~~~~~

As you can see, there are assignment operators and implicit operators which allow you to use the rapidschema class 
just as if it really was a struct. The compiler however cannot apply these conversions in all situations. As a fallback
rapidschema therefore also provides the .Get() method on all properties.

## That's All?

No, not at all. There are a number of other cool features in rapidschema which are absolutely worth exploring. Keep
reading on!

## Json Schema Validation

Ever heard that there is a json schema? A json schema is similar to an xml schema. It allows defining the structure 
and also some constraints on the content of json data in json. It allows you to write json files which specify 
a schema for other json files.
[Understanding JSON schema](https://json-schema.org/understanding-json-schema/) is a great resource if you want to get
a quick impression. The [JSON Schema Validator](https://www.jsonschemavalidator.net/) allows you to play with json
schemas and verify your understanding. The [official json schema specification](https://json-schema.org/) is currently 
at draft-07 and is actively aiming at reaching the RFC status.

So why is this relevant? Rapidschema allows you to define a json schema in code. Transform a json string into the schema and
validate all the schema constraints. During schema validation, as with parsing, it again collects a list of all errors 
 encountered and reports this error list once done.

As a simple example consider the case where you wish to constrain the range of a double value. This can be done using 
[Range](https://json-schema.org/understanding-json-schema/reference/numeric.html#range) constraints such as Minimum /
Maximum. In rapidschema the corresponding code for an object containing such a range constraint value will look as
follows:

~~~~~~~~~~cpp
//file: examples/simple_schema.cpp
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
    : integer_value(MakeValue<int, Minimum>(Minimum(10)))
    , string_value(MakeValue<std::string, MaxLength>(MaxLength(20))) {}

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

  return 0;
}
~~~~~~~~~~

When run this example will output the following:

~~~~~~~~~~shell
Transform Error 1 is located at: "integerValue" and the corresponding message is: Expected: >= 10. Actual: 5
Transform Error 2 is located at: "stringValue" and the corresponding message is: Expected string of length at most 20. Actual: length 24 string: "My dog wears sunglasses!"
Transform Error 3 is located at: "" and the corresponding message is: Unexpected member encountered: additionalProperty
~~~~~~~~~~

The example also shows how to change the behavior of the object class such that errors are reported when additional 
properties are present in the json string.

Since transformation and validation are separate steps / functions you can also build an object in C++ as shown in
 the serialization example and then validate the data against the schema without ever serializing it.

However, with a jsonschema much more can be done. Please consult the [full list of supported json schema features](TODO)
to see which json schema features are supported by rapidschema. Consult the above references for inspiration on what 
can be done using a json schema.

## Cross Validation

NOT YET IMPLEMENTED...

Even though a json schema is quite flexible, you will not be able to express all the cross dependencies of a complex 
configuration file. What if you have a list of persons, each of which must have a id which must be unique accross all
persons? This is a simple example of a constraint which cannot be expressed in a json schema. During cross validation 
rapidschema allows you to express more involved cross dependencies in code. Here you have all the flexibility in the 
world.

~~~~~~~~~~cpp
TODO
~~~~~~~~~~

## Implement a Hard Shell

Cross validation combined with the json schema constraints allows you to build a hard shell for external 
json input. If done properly you can reject any invalid configuration right after parsing. Validating user and 
other external input at the boundary of your software will have a tremendous impact on the quality of the source code
at its core. Since the configuration has been validated you will no longer need to handle any kind of exceptional 
conditions. You can simply assert. This will prevent you from getting slogged down by c-style error handling or complex 
exception handling.

TODO links

## A Note on Designing Complex Configuration Files

Complex applications often require complex configuration files. The structure of these files therefore needs to be 
defined. If this structure is defined by the application developer the developer may choose to reflect the structure of
the source code in the structure of the json file. This then greatly simplifies converting the configuration
file into objects used at runtime.

However, we would like to pledge here that such a choice is a bad one and quickly becomes problematic. Normally the 
structure of the configuration file tends to be suboptimal for the user. Once the software is release, there soon will
be a large number of configuration files which also need to be maintained. This is followed by a breaking feature 
request which requires restructuring the source code. Now you are likely to realize that the code base exhibits a 
tight coupling between the structure of the source code and the structure of the configuration file. Changing
the source code requires changing the structure of the configuration files and this is something you 
cannot do, because the users will get mad at you.

This is why we believe its better to keep the configuration code as seperate as possible from the rest of
the production code. Try to build factories which take the configuration object and generate production
objects from them. This will allow you to evolve the structure of the production code and the structure
of the configuration separately. You can provide the user with optimal configuration files while maintaining a clean
code base at the expense of writing factory classes which translate between the two worlds.

By the way: this was a hard lesson learnt ;-)

## Schema Evolution

This brings us to the question whether rapidschema provides special support for schema evolution. The answer is
it does have some basic features such as [default values](TODO) and [optional values](TODO). These allow
you to add new properties to your schema or remove properties without breaking all existing configuration
files. These features are also part of the json schema standard. Rapidschema is not planning to implement features
beyond the json schema specification.

Needless to say that in complex situations its much easier to write code which transforms one rapidschema configuration 
into another rather than working directly on the json string.

## Overlays

NOT YET IMPLEMENTED...

Rapidschema also provides config overlays. Simply put you can parse some kind of base configuration, and then parse
any number of overlay configurations which do not contain a complete configuration, but only part thereof. The values
contained in the overlay configuration will be overwritten. This can be useful if you have a large number of 
very similar configurations.

~~~~~~~~~~cpp
TODO
~~~~~~~~~~

Since parsing, validation, cross validation and overlays are separate functions in rapidschema you can freely combine 
them. It is up to you whether you with do validate and cross validate all intermediate configurations or only the final 
result.

## Generating a Json Schema from Code

Json schemas are useful for defining the structure of json data not only for configuration files but also when 
communicating between web services or micro services. In this case you may need to parse the data in C++ as well
as other programming languages. This may also be the case if your application is written in C++ and you want to
provide a Java tool for editing the configuration. Wouldn't it be great if you only needed to define the structure of 
the json data in one place and do not need to maintain all the different implementations separately?

Currently not all features of rapidschema are supported. Adding more features should now be relatively straight 
forward.

An example is shown.

~~~~~~~~~~cpp
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
      : integer_value(MakeValue<int, Minimum>(Minimum(10)))
      , string_value(MakeValue<std::string, MaxLength>(MaxLength(20))) {}

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
~~~~~~~~~~

This will generate the following schema:

~~~~~~~~~~json
{
    "type": "object",
    "properties": {
        "stringValue": {
            "type": "string",
            "maxLength": 20
        },
        "integerValue": {
            "type": "integer",
            "minimum": 10
        }
    },
    "required": [
        "integerValue",
        "stringValue"
    ]
}
~~~~~~~~~~

If you try to validate the json generated by the serialization example against this schema it will fail. Which is
something you can find out before hand by calling Validate() on the object.

If you which to use this feature you need to add -DRAPIDSCHEMA_WITH_SCHEMA_GENERATION option to the command line
when invoking cmake. E.g.

~~~~~~~~~~shell
 cmake -DCMAKE_BUILD_TYPE=Release -DRAPIDSCHEMA_WITH_SCHEMA_GENERATION ..
~~~~~~~~~~

## Generating Code from Schema

NOT YET IMPLEMENTED...

The other direction currently seems more difficult. Nevertheless, it would be great to be able to generate Code also
from a schema.

Conceptually this is similar to how for instance [protobuf](https://developers.google.com/protocol-buffers/) works. 
You specify a schema and it will generate the serialization and deserialization code for you - in pretty much any 
language. Rapidschema aims at providing the C++ binding for json schemas.


## Performance

Rapidschema was built with performance in mind. Specifically, it is optimized for parsing json without encountering any
errors. While rapidschema may be slower than other json parsers, it also does more work. It not only parses the input, 
but also validates it - work which is normally left to the user of the library and in most situations cannot be avoided. 
Hence, the comparison below is not fair. Keep this in mind while studying the numbers below.

TODO: Build and show benchmark results....

## Advanced Features

### Features Inherited from Rapidjson

Rapidschema is based on rapidjson - which is an extremely versatile and fast json parser. While rapidschema tries to
make the fact that its based on rapidjson transparent to the basic user, an advanced user needs to also read the 
rapidjson documentation. This will allow you to take full advantage of the underlying features and flexibility.

#### Different Encodings

Rapidjson supports a number of different encodings: utf8, utf16, utf32. So does rapidschema.

TODO example

#### Pretty printing vs compressed printing

TODO example

### Custom types

Rapidschema already allows you to parse any of the basic types, including strings into objects. However, you wish
to parse the json int directly into an std::chrono::milliseconds. No problem, there is a way to extend rapidschema to 
allow you to do exactly this.

TODO example

### C++ Concepts

Rapidschema at its core makes use of template meta programming. This has the effect that if you make a mistake when
using the library you may get hard to understand compilation errors deep down in the rapidschema library.

If you are using gcc you can provide the compiler the -fconcepts flag and define RAPIDSCHEMA_WITH_CONCEPTS when 
compiling. C++ concepts will be part of the C++20 standard and greatly alleviate this pain.

## State of the Project

Rapidschema is still in an early state of its development. Which means that currently there is no real world project 
using it. Nevertheless we are convinced that for many projects using a library such as rapidschema would be
a great benefit and for most basic use cases rapidschema is already a great asset as is.

If you decide to try it out or actually use it in your project please let us know. Of course bug reports or reports of
other defects such a missing documentation or broken build files are more than welcome!

## Getting Started

Prerequisites:

Rapidschema makes use of C++17 features such as std::optional and std::variant. Generally, using rapidschema with 
a C++17 compatible compiler will be smoother due to the improve template support in the language. The following is 
tested with gcc-7 and clang-5. Compiling rapidschema with a C++17 compiler amounts to:

~~~~~~~~~~shell
git clone https://github.com/ledergec/rapidschema.git
cd rapidschema
git submodule update --init --recursive
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
~~~~~~~~~~

It is possible, however, to use rapidschema with a C++11 compiler. This is implemented using a C++11 compatible 
implementation of std::optional and other C++17 stl features found in [abseil.io](https://abseil.io/) and is 
tested with gcc-5 and clang 3.5. In order to build using the C++11 backport use the following commands:

~~~~~~~~~~shell
git clone https://github.com/ledergec/rapidschema.git
cd rapidschema
git submodule update --init --recursive
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DRAPIDSCHEMA_CPP_11=ON ..
make
~~~~~~~~~~

If you are not using cmake to build you will still need to #define RAPIDSCHEMA_CPP_11 in order to enable the use of 
abseil within rapidschema.

Rapidschema makes use of cmake as a build system. Hence integrating it will be straight forward if you are using cmake 
yourself. However, rapidschema is a header only library and its dependencies either are header only (rapidjson) or have
a header only mode (libfmt). Only abseil.io needs to be linked to - another reason to use C++17.

If you run into problems when integrating or have remarks on the cmake build scripts contained in the 
rapidschema source base please let us know.

## Contributing

TODO describe docker container containing clion installation. Point out that a license is necessary.