// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_SCHEMA_STRING_SCHEMA_H_
#define INCLUDE_RAPIDSCHEMA_SCHEMA_STRING_SCHEMA_H_

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION

#include "rapidschema/schema/string_schema_interface.h"

namespace rapidschema {
namespace schema {

class StringSchema : public TypeSchema ,
                     public StringSchemaInterface {
 public:
  StringSchema();

  OptionalConfig<Value<uint32_t>> min_length;
  OptionalConfig<Value<uint32_t>> max_length;

  void SetMinLength(size_t min) override;
  void SetMaxLength(size_t max) override;

  std::shared_ptr<SubSchema> CreateSubSchema() const override;

 protected:
  PropertyMapping CreatePropertyMapping() const override;
};

}  // namespace schema
}  // namespace rapidschema

#endif

#endif  // INCLUDE_RAPIDSCHEMA_SCHEMA_STRING_SCHEMA_H_
