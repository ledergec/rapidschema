// Copyright (C) 2019 Christian Ledergerber

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION

#include "rapidschema/schema/schema.h"

namespace rapidschema {
namespace schema {

NumberSchema::NumberSchema() {
  type = "number";
  type.SetExpectedValue("number");
}

void NumberSchema::SetMultipleOf(double multiple) {
  multiple_of = multiple;
}

void NumberSchema::SetMinimum(double min) {
  minimum = min;
}

void NumberSchema::SetExclusiveMinimum(double exclusive_min) {
  exclusive_minimum = exclusive_min;
}

void NumberSchema::SetMaximum(double max) {
  maximum = max;
}

void NumberSchema::SetExclusiveMaximum(double exclusive_max) {
  exclusive_maximum = exclusive_max;
}

std::shared_ptr<SubSchema> NumberSchema::CreateSubSchema() const {
  return std::make_shared<SubSchema>(*this);
}

NumberSchema::PropertyMapping NumberSchema::CreatePropertyMapping() const {
  PropertyMapping property_mapping(
      {{"multipleOf", &multiple_of},
       {"minimum", &minimum},
       {"exclusiveMinimum", &exclusive_minimum},
       {"maximum", &maximum},
       {"exclusiveMaximum", &exclusive_maximum}});

  auto mapping = TypeSchema::CreatePropertyMapping();
  mapping.insert(std::end(mapping), std::begin(property_mapping), std::end(property_mapping));
  return mapping;
}

}  // namespace schema
}  // namespace rapidschema

#endif
