// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_SCHEMA_NUMBER_SCHEMA_H_
#define INCLUDE_RAPIDSCHEMA_SCHEMA_NUMBER_SCHEMA_H_

#include <memory>

#include "rapidschema/optional_config.h"
#include "rapidschema/schema/type_schema.h"

namespace rapidschema {
namespace schema {

class NumberSchema : public TypeSchema {
 public:
  NumberSchema() {
    type.SetExpectedValue("number");
  }

  OptionalConfig<Value<double>> multiple_of;
  OptionalConfig<Value<double>> minimum;
  OptionalConfig<Value<double>> exclusive_minimum;
  OptionalConfig<Value<double>> maximum;
  OptionalConfig<Value<double>> exclusive_maximum;

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

#endif  // INCLUDE_RAPIDSCHEMA_SCHEMA_NUMBER_SCHEMA_H_
