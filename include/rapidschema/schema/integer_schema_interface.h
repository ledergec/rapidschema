// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_SCHEMA_INTEGER_SCHEMA_INTERFACE_H_
#define INCLUDE_RAPIDSCHEMA_SCHEMA_INTEGER_SCHEMA_INTERFACE_H_

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION

#include <inttypes.h>

#include "rapidschema/schema/sub_schema_interface.h"

namespace rapidschema {
namespace schema {

class IntegerSchemaInterface : public SubSchemaInterface {
 public:
  virtual void SetMultipleOf(int64_t multiple) = 0;
  virtual void SetMinimum(int64_t minimum) = 0;
  virtual void SetExclusiveMinimum(int64_t exclusive_minimum) = 0;
  virtual void SetMaximum(int64_t maximum) = 0;
  virtual void SetExclusiveMaximum(int64_t exclusive_maximum) = 0;
};

}  // namespace schema
}  // namespace rapidschema

#endif

#endif  // INCLUDE_RAPIDSCHEMA_SCHEMA_INTEGER_SCHEMA_INTERFACE_H_
