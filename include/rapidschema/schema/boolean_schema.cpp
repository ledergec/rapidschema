// Copyright (C) 2019 Christian Ledergerber

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION

#include "rapidschema/schema/schema.h"

namespace rapidschema {
namespace schema {

BooleanSchema::BooleanSchema() {
  type = "boolean";
  type.SetExpectedValue("boolean");
}

std::shared_ptr<SubSchema> BooleanSchema::CreateSubSchema() const {
  return std::make_shared<SubSchema>(*this);
}

BooleanSchema::PropertyMapping BooleanSchema::CreatePropertyMapping() const {
  return {};
}

}  // namespace schema
}  // namespace rapidschema

#endif
