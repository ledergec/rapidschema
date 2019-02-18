// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_SCHEMA_BOOLEAN_SCHEMA_INTERFACE_H_
#define INCLUDE_RAPIDSCHEMA_SCHEMA_BOOLEAN_SCHEMA_INTERFACE_H_

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION

#include <inttypes.h>

#include "rapidschema/schema/sub_schema_interface.h"

namespace rapidschema {
namespace schema {

class BooleanSchemaInterface : public SubSchemaInterface {
};

}  // namespace schema
}  // namespace rapidschema

#endif

#endif  // INCLUDE_RAPIDSCHEMA_SCHEMA_BOOLEAN_SCHEMA_INTERFACE_H_
