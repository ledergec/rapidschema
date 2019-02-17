// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_SCHEMA_TYPE_SCHEMA_H_
#define INCLUDE_RAPIDSCHEMA_SCHEMA_TYPE_SCHEMA_H_

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION

#include "rapidschema/constant.h"
#include "rapidschema/no_additional_properties.h"
#include "rapidschema/object.h"

namespace rapidschema {
namespace schema {

class TypeSchema : public NoAdditionalProperties<Object> {
 public:
  Constant<std::string> type;

 protected:
  PropertyMapping CreatePropertyMapping() const override {
    return {{"type", &type}};
  }
};

}  // namespace schema
}  // namespace rapidschema

#endif

#endif  // INCLUDE_RAPIDSCHEMA_SCHEMA_TYPE_SCHEMA_H_
