// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_SCHEMA_BOOLEAN_SCHEMA_H_
#define INCLUDE_RAPIDSCHEMA_SCHEMA_BOOLEAN_SCHEMA_H_

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION

#include "rapidschema/schema/boolean_schema_interface.h"
#include "rapidschema/schema/type_schema.h"

namespace rapidschema {
namespace schema {

class BooleanSchema : public TypeSchema,
                      public BooleanSchemaInterface {
 public:
  BooleanSchema();

  std::shared_ptr<SubSchema> CreateSubSchema() const override;

 protected:
  PropertyMapping CreatePropertyMapping() const override;
};

}  // namespace schema
}  // namespace rapidschema

#endif

#endif  // INCLUDE_RAPIDSCHEMA_SCHEMA_BOOLEAN_SCHEMA_H_
