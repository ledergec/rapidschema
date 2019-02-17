// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_SCHEMA_INTEGER_SCHEMA_H_
#define INCLUDE_RAPIDSCHEMA_SCHEMA_INTEGER_SCHEMA_H_

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION

#include "rapidschema/optional_config.h"
#include "rapidschema/schema/type_schema.h"

namespace rapidschema {
namespace schema {

class IntegerSchema : public TypeSchema {
 public:
  IntegerSchema() {
    type.SetExpectedValue("integer");
  }

  OptionalConfig<Value<int64_t>> multiple_of;
  OptionalConfig<Value<int64_t>> minimum;
  OptionalConfig<Value<int64_t>> exclusive_minimum;
  OptionalConfig<Value<int64_t>> maximum;
  OptionalConfig<Value<int64_t>> exclusive_maximum;

 protected:
  PropertyMapping CreatePropertyMapping() const override {
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
};

}  // namespace schema
}  // namespace rapidschema

#endif

#endif  // INCLUDE_RAPIDSCHEMA_SCHEMA_INTEGER_SCHEMA_H_
