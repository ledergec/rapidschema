//
// Created by Christian Ledergerber on 15.11.18.
//

// Reading a message JSON with Reader (SAX-style API).
// The JSON should be an object with key-string pairs.

#include <string>
#include <iostream>

#include "rapidjson/document.h"
#include "rapidjson/error/en.h"

#include "confignode.h"
#include "configvalue.h"
#include "string_constraints.h"
#include "type_set.h"
#include "variant.h"

using namespace rapidjson;
using namespace rapidoson;

class ConfigExample : public ConfigNode {
public:
    ConfigExample()
            : ConfigNode("example", {&integer_value, &string_value})
            , integer_value("integerValue")
            , string_value("stringValue") {}

    ConfigValue<int> integer_value;
    ConfigValue<std::string, MinLength<2>,
                             MaxLength<3>> string_value;
};

class NestedConfigExample : public ConfigNode {
public:
    NestedConfigExample()
            : ConfigNode("nestedExample", {&example, &integer_value, &string_value})
            , integer_value("integerValue")
            , string_value("stringValue") {}

    ConfigExample example;
    ConfigValue<int> integer_value;
    ConfigValue<std::string> string_value;
};

static void ParseString(const char* json, Config * config) {
    Document document;
    ParseResult result = document.Parse(json);
    if (result.IsError()) {
        std::cout << "Could not parse input" << std::endl;
        return;
    }

    auto transform_result = config->Parse(document);
    if (transform_result.Success()) {
        std::cout << "Successfully parsed" << std::endl;
    } else {
        std::cout << transform_result.GetPath() << " failed parsing because " << transform_result.GetMessage() << std::endl;
    }
}

int main() {
    ConfigExample example;
    ParseString(R"(
                {
                  "integerValue": 23,
                  "stringValue": "hallo"
                }
                )", &example);

    std::cout << "integerValue: " << example.integer_value.Get() << std::endl;
    std::cout << "stringValue: " << example.string_value.Get() << std::endl;

    auto valid = example.Validate();
    if (valid.Success()) {
        std::cout << "validation success" << std::endl;
    } else {
        std::cout << "validation failed: " << std::endl;
        std::cout << valid.GetPath() << ": " << valid.GetMessage() << std::endl;
    }

    NestedConfigExample nested_example;
    ParseString(R"(
                {
                  "example": {
                    "integerValue": 43,
                    "stringValue": "nested_value"
                  },
                  "integerValue": 23,
                  "stringValue": "hallo"
                }
                )", &nested_example);

    std::cout << "example.integerValue: " << nested_example.example.integer_value.Get() << std::endl;
    std::cout << "example.stringValue: " << nested_example.example.string_value.Get() << std::endl;
    std::cout << "integerValue: " << nested_example.integer_value.Get() << std::endl;
    std::cout << "stringValue: " << nested_example.string_value.Get() << std::endl;


    ParseString(R"(
                {
                  "example": {
                    "integerVlue": 43,
                    "stringValue": "nested_value"
                  },
                  "integerValue": 23,
                  "stringValue": "hallo"
                }
                )", &nested_example);

    using IntStringBool = TypeSet<int, std::string, bool>;
    static_assert(IntStringBool::Unique(), "IntStringBool::Unique() should return true");
    static_assert(IntStringBool::Contains<float>(), "IntStringBool contains float");
    static_assert(IntStringBool::Contains<std::nullptr_t>() == false, "IntStringBool does not contain nullptr_t");

    using IntFloatBool = TypeSet<int, float, bool>;
    static_assert(IntFloatBool::Unique() == false, "IntFloatBool::Unique() should return false");
    return 0;
}
