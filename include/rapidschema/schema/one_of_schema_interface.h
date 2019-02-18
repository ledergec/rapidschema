// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_SCHEMA_ONE_OF_SCHEMA_INTERFACE_H_
#define INCLUDE_RAPIDSCHEMA_SCHEMA_ONE_OF_SCHEMA_INTERFACE_H_

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION

#include "rapidschema/schema/sub_schema_interface.h"

namespace rapidschema {
namespace schema {

class OneOfSchemaInterface : public SubSchemaInterface {
 public:
  virtual void AddVariant(std::shared_ptr<SubSchema> sub_schema) = 0;

  virtual std::shared_ptr<SubSchema> CreateSubSchema() const = 0;
};

}  // namespace schema
}  // namespace rapidschema

#endif

#endif  // INCLUDE_RAPIDSCHEMA_SCHEMA_ONE_OF_SCHEMA_INTERFACE_H_
