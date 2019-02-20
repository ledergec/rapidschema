// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_SCHEMA_INTEGER_SCHEMA_H_
#define INCLUDE_RAPIDSCHEMA_SCHEMA_INTEGER_SCHEMA_H_

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION

#include "rapidschema/optional_config.h"
#include "rapidschema/schema/integer_schema_interface.h"
#include "rapidschema/schema/type_schema.h"

namespace rapidschema {
namespace schema {

class IntegerSchema : public TypeSchema,
                      public IntegerSchemaInterface {
 public:
  IntegerSchema();

  OptionalConfig<Value<int64_t>> multiple_of;
  OptionalConfig<Value<int64_t>> minimum;
  OptionalConfig<Value<int64_t>> exclusive_minimum;
  OptionalConfig<Value<int64_t>> maximum;
  OptionalConfig<Value<int64_t>> exclusive_maximum;

  void SetMultipleOf(int64_t multiple) override;

  void SetMinimum(int64_t min) override;

  void SetExclusiveMinimum(int64_t exclusive_min) override;

  void SetMaximum(int64_t max) override;

  void SetExclusiveMaximum(int64_t exclusive_max) override;

  std::shared_ptr<SubSchema> CreateSubSchema() const override;

 protected:
  PropertyMapping CreatePropertyMapping() const override;
};

}  // namespace schema
}  // namespace rapidschema

#endif

#endif  // INCLUDE_RAPIDSCHEMA_SCHEMA_INTEGER_SCHEMA_H_
