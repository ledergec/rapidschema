// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_SCHEMA_NUMBER_SCHEMA_INTERFACE_H_
#define INCLUDE_RAPIDSCHEMA_SCHEMA_NUMBER_SCHEMA_INTERFACE_H_

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION

#include "rapidschema/schema/sub_schema_interface.h"

namespace rapidschema {
namespace schema {

class NumberSchemaInterface : public SubSchemaInterface {
 public:
  virtual void SetMultipleOf(double multiple) = 0;
  virtual void SetMinimum(double minimum) = 0;
  virtual void SetExclusiveMinimum(double exclusive_minimum) = 0;
  virtual void SetMaximum(double maximum) = 0;
  virtual void SetExclusiveMaximum(double exclusive_maximum) = 0;
};

}  // namespace schema
}  // namespace rapidschema

#endif

#endif  // INCLUDE_RAPIDSCHEMA_SCHEMA_NUMBER_SCHEMA_INTERFACE_H_
