// Copyright (C) 2019 Christian Ledergerber

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION

#include "integer_schema.h"

#include "rapidschema/schema/sub_schema.h"

namespace rapidschema {
namespace schema {

IntegerSchema::IntegerSchema() {
  type = "integer";
  type.SetExpectedValue("integer");
}

void IntegerSchema::SetMultipleOf(int64_t multiple) {
  multiple_of = multiple;
}

void IntegerSchema::SetMinimum(int64_t min) {
  minimum = min;
}

void IntegerSchema::SetExclusiveMinimum(int64_t exclusive_min) {
  exclusive_minimum = exclusive_min;
}

void IntegerSchema::SetMaximum(int64_t max) {
  maximum = max;
}

void IntegerSchema::SetExclusiveMaximum(int64_t exclusive_max) {
  exclusive_maximum = exclusive_max;
}

std::shared_ptr<SubSchema> IntegerSchema::CreateSubSchema() const {
  return std::make_shared<SubSchema>(*this);
}

IntegerSchema::PropertyMapping IntegerSchema::CreatePropertyMapping() const {
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
