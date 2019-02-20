// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_SCHEMA_NUMBER_SCHEMA_H_
#define INCLUDE_RAPIDSCHEMA_SCHEMA_NUMBER_SCHEMA_H_

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION

#include "rapidschema/optional_config.h"
#include "rapidschema/schema/number_schema_interface.h"
#include "rapidschema/schema/type_schema.h"

namespace rapidschema {
namespace schema {

class NumberSchema : public TypeSchema ,
                     public NumberSchemaInterface {
 public:
  NumberSchema();

  OptionalConfig<Value<double>> multiple_of;
  OptionalConfig<Value<double>> minimum;
  OptionalConfig<Value<double>> exclusive_minimum;
  OptionalConfig<Value<double>> maximum;
  OptionalConfig<Value<double>> exclusive_maximum;


  void SetMultipleOf(double multiple) override;

  void SetMinimum(double min) override;

  void SetExclusiveMinimum(double exclusive_min) override;

  void SetMaximum(double max) override;

  void SetExclusiveMaximum(double exclusive_max) override;

  std::shared_ptr<SubSchema> CreateSubSchema() const override;

 protected:
  PropertyMapping CreatePropertyMapping() const override;
};

}  // namespace schema
}  // namespace rapidschema

#endif

#endif  // INCLUDE_RAPIDSCHEMA_SCHEMA_NUMBER_SCHEMA_H_
