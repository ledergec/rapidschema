// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_SCHEMA_STRING_SCHEMA_H_
#define INCLUDE_RAPIDSCHEMA_SCHEMA_STRING_SCHEMA_H_

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION

#include "rapidschema/optional_config.h"
#include "rapidschema/schema/type_schema.h"

namespace rapidschema {
namespace schema {

class StringSchema : public TypeSchema {
 public:
  StringSchema() {
    type.SetExpectedValue("string");
  }

  OptionalConfig<Value<size_t>> min_length;
  OptionalConfig<Value<size_t>> max_length;

 protected:
  PropertyMapping CreatePropertyMapping() const override {
    PropertyMapping property_mapping(
        {{"minLength", &min_length},
         {"maxLength", &max_length}});

    auto mapping = TypeSchema::CreatePropertyMapping();
    mapping.insert(std::end(mapping), std::begin(property_mapping), std::end(property_mapping));
    return mapping;
  }
};

}  // namespace schema
}  // namespace rapidschema

#endif

#endif  // INCLUDE_RAPIDSCHEMA_SCHEMA_STRING_SCHEMA_H_
