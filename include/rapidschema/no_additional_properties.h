// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_NO_ADDITIONAL_PROPERTIES_H_
#define INCLUDE_RAPIDSCHEMA_NO_ADDITIONAL_PROPERTIES_H_

#include <fmt/format.h>

#include "rapidschema/result.h"

namespace rapidschema {

template<typename BaseObject>
class NoAdditionalProperties : public BaseObject {
 public:
  bool AdditionalPropertiesAllowed() const override {
    return false;
  }
};

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_NO_ADDITIONAL_PROPERTIES_H_
