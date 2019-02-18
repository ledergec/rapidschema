// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_SCHEMA_SCHEMA_H_
#define INCLUDE_RAPIDSCHEMA_SCHEMA_SCHEMA_H_

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION

#include <assert.h>

#include <memory>

#include "rapidschema/array.h"
#include "rapidschema/constant.h"
#include "rapidschema/no_additional_properties.h"
#include "rapidschema/object.h"
#include "rapidschema/one_of.h"
#include "rapidschema/pattern_property.h"
#include "rapidschema/optional_config.h"

#include "rapidschema/schema/sub_schema_interface.h"
#include "rapidschema/schema/type_schema.h"

#include "rapidschema/schema/boolean_schema.h"
#include "rapidschema/schema/constant_schema.h"
#include "rapidschema/schema/integer_schema.h"
#include "rapidschema/schema/number_schema.h"
#include "rapidschema/schema/string_schema.h"
#include "rapidschema/schema/object_schema.h"
#include "rapidschema/schema/one_of_schema.h"
#include "rapidschema/schema/sub_schema.h"

#include "rapidschema/schema/constant_schema_impl.h"

#endif

#endif  // INCLUDE_RAPIDSCHEMA_SCHEMA_SCHEMA_H_
