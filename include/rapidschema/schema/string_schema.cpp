// Copyright (C) 2019 Christian Ledergerber

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION

#include "rapidschema/schema/schema.h"

namespace rapidschema {
namespace schema {

StringSchema::StringSchema() {
  type.SetExpectedValue("string");
}

void StringSchema::SetMinLength(size_t min) {
  min_length = min;
}

void StringSchema::SetMaxLength(size_t max) {
  max_length = max;
}

std::shared_ptr<SubSchema> StringSchema::CreateSubSchema() const {
  return std::make_shared<SubSchema>(*this);
}

StringSchema::PropertyMapping StringSchema::CreatePropertyMapping() const {
  PropertyMapping property_mapping(
      {{"minLength", &min_length},
       {"maxLength", &max_length}});

  auto mapping = TypeSchema::CreatePropertyMapping();
  mapping.insert(std::end(mapping), std::begin(property_mapping), std::end(property_mapping));
  return mapping;
}

}  // namespace schema
}  // namespace rapidschema

#endif
