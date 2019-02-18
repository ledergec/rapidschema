// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_SCHEMA_OBJECT_SCHEMA_INTERFACE_H_
#define INCLUDE_RAPIDSCHEMA_SCHEMA_OBJECT_SCHEMA_INTERFACE_H_

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION

#include "rapidschema/schema/sub_schema_interface.h"

namespace rapidschema {
namespace schema {

class ObjectSchemaInterface : public SubSchemaInterface {
 public:
  virtual void AddProperty(const std::string& name, std::shared_ptr<SubSchema> schema) = 0;
  virtual void AddPatternProperty(const std::string& regex, std::shared_ptr<SubSchema> schema) = 0;

  virtual void SetAdditionalProperties(bool additional_props) = 0;
  virtual void AddRequired(const std::string& required) = 0;
};

}  // namespace schema
}  // namespace rapidschema

#endif

#endif  // INCLUDE_RAPIDSCHEMA_SCHEMA_OBJECT_SCHEMA_INTERFACE_H_
