// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_SCHEMA_SUB_SCHEMA_INTERFACE_H_
#define INCLUDE_RAPIDSCHEMA_SCHEMA_SUB_SCHEMA_INTERFACE_H_

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION

#include <memory>

namespace rapidschema {
namespace schema {

class SubSchema;

class SubSchemaInterface {
 public:
  virtual std::shared_ptr<SubSchema> CreateSubSchema() const = 0;
};

}  // namespace schema
}  // namespace rapidschema

#endif

#endif  // INCLUDE_RAPIDSCHEMA_SCHEMA_SUB_SCHEMA_INTERFACE_H_
