// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_SCHEMA_OBJECT_SCHEMA_H_
#define INCLUDE_RAPIDSCHEMA_SCHEMA_OBJECT_SCHEMA_H_

#include <memory>

#include "rapidschema/array.h"
#include "rapidschema/one_of.h"
#include "rapidschema/optional_config.h"
#include "rapidschema/schema/integer_schema.h"
#include "rapidschema/schema/number_schema.h"
#include "rapidschema/schema/string_schema.h"
#include "rapidschema/schema/type_schema.h"

namespace rapidschema {
namespace schema {

class ObjectSchema;

using AnySchema = OneOf<ObjectSchema,
                        NumberSchema,
                        IntegerSchema,
                        StringSchema>;

class PropertiesSchema : public NoAdditionalProperties<Object> {
 public:
  PropertiesSchema();

  std::shared_ptr<PatternProperty<AnySchema>> pattern_properties;

 protected:
  PatternPropertyList CreatePatternPropertyList() const override;
};


class PatternPropertiesSchema : public NoAdditionalProperties<Object> {
 public:
  PatternPropertiesSchema();

  std::shared_ptr<PatternProperty<AnySchema>> properties;

 protected:
  PatternPropertyList CreatePatternPropertyList() const override;
};


class ObjectSchema : public TypeSchema {
 public:
  ObjectSchema() {
    type.SetExpectedValue("object");
  }

  OptionalConfig<PropertiesSchema> properties;

  OptionalConfig<PatternPropertiesSchema> pattern_properties;

  OptionalConfig<Value<bool>> additional_properties;

  void AddRequired(const std::string & required_property) {
    if (required.HasValue() == false) {
      required = Array<Value<std::string>>();
    }
    required.GetValue().push_back(required_property);
  }

 protected:
  PropertyMapping CreatePropertyMapping() const override {
    PropertyMapping property_mapping(
        {{"properties", &properties},
         {"patternProperties", &pattern_properties},
         {"additionalProperties", &additional_properties},
         {"required", &required}});

    auto mapping = TypeSchema::CreatePropertyMapping();
    mapping.insert(std::end(mapping), std::begin(property_mapping), std::end(property_mapping));
    return mapping;
  }

 private:
  OptionalConfig<Array<Value<std::string>>> required;
};

///////////////////// Implementation of PropertiesSchema ////////////////////////////////////
PropertiesSchema::PropertiesSchema()
    : pattern_properties(std::make_shared<PatternProperty<AnySchema>>(Regex<>::AnyRegex())) {}

PropertiesSchema::PatternPropertyList PropertiesSchema::CreatePatternPropertyList() const {
  return {pattern_properties.get()};
}


///////////////////// Implementation of PatternPropertiesSchema ////////////////////////////////////
PatternPropertiesSchema::PatternPropertiesSchema()
      : properties(std::make_shared<PatternProperty<AnySchema>>(Regex<>::AnyRegex())) {}

PatternPropertiesSchema::PatternPropertyList PatternPropertiesSchema::CreatePatternPropertyList() const {
    return {properties.get()};
  }

}  // namespace schema
}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_SCHEMA_OBJECT_SCHEMA_H_
