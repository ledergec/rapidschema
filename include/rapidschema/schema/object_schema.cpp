// Copyright (C) 2019 Christian Ledergerber

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION

#include "rapidschema/schema/schema.h"

namespace rapidschema {
namespace schema {

PropertiesSchema::PropertiesSchema()
    : properties(std::make_shared<PatternProperty<SubSchema>>(Regex<>::AnyRegex())) {}

PropertiesSchema::PatternPropertyList PropertiesSchema::CreatePatternPropertyList() const {
  return {properties.get()};
}


PatternPropertiesSchema::PatternPropertiesSchema()
    : pattern_properties(std::make_shared<PatternProperty<SubSchema>>(Regex<>::AnyRegex())) {}

PatternPropertiesSchema::PatternPropertyList PatternPropertiesSchema::CreatePatternPropertyList() const {
  return {pattern_properties.get()};
}

ObjectSchema::ObjectSchema()
  : properties(std::make_shared<OptionalConfig<PropertiesSchema>>())
  , pattern_properties(std::make_shared<OptionalConfig<PatternPropertiesSchema>>()) {
  type = "object";
  type.SetExpectedValue("object");
}

void ObjectSchema::AddProperty(const std::string& name, std::shared_ptr<SubSchema> schema) {
  if (properties->HasValue() == false) {
    *properties = PropertiesSchema();
  }

  properties->GetValue().properties->Insert(name, *schema);
}

void ObjectSchema::AddPatternProperty(const std::string& regex, std::shared_ptr<SubSchema> schema) {
  if (pattern_properties->HasValue() == false) {
    *pattern_properties = PatternPropertiesSchema();
  }

  pattern_properties->GetValue().pattern_properties->Insert(regex, *schema);
}

void ObjectSchema::SetAdditionalProperties(bool additional_props) {}

void ObjectSchema::AddRequired(const std::string & required_property) {
  if (required.HasValue() == false) {
    required = Array<Value<std::string>>();
  }
  required.GetValue().push_back(required_property);
}

std::shared_ptr<SubSchema> ObjectSchema::CreateSubSchema() const {
  return std::make_shared<SubSchema>(*this);
}

ObjectSchema::PropertyMapping ObjectSchema::CreatePropertyMapping() const {
  PropertyMapping property_mapping(
      {{"properties", properties.get()},
       {"patternProperties", pattern_properties.get()},
       {"additionalProperties", &additional_properties},
       {"required", &required}});

  auto mapping = TypeSchema::CreatePropertyMapping();
  mapping.insert(std::end(mapping), std::begin(property_mapping), std::end(property_mapping));
  return mapping;
}

}  // namespace schema
}  // namespace rapidschema

#endif
