// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_SCHEMA_STRING_SCHEMA_INTERFACE_H_
#define INCLUDE_RAPIDSCHEMA_SCHEMA_STRING_SCHEMA_INTERFACE_H_

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION

#include "rapidschema/schema/sub_schema_interface.h"

namespace rapidschema {
namespace schema {

class StringSchemaInterface : public SubSchemaInterface {
 public:
  virtual void SetMinLength(size_t min) = 0;
  virtual void SetMaxLength(size_t max) = 0;
};

}  // namespace schema
}  // namespace rapidschema

#endif

#endif  // INCLUDE_RAPIDSCHEMA_SCHEMA_STRING_SCHEMA_INTERFACE_H_
