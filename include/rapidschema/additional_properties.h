// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_ADDITIONAL_PROPERTIES_H_
#define INCLUDE_RAPIDSCHEMA_ADDITIONAL_PROPERTIES_H_

#include "rapidschema/result.h"

namespace rapidschema {

template<typename BaseObject>
class AdditionalProperties : public BaseObject {
 public:
  bool AdditionalPropertiesAllowed() const override {
    return true;
  }
};

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_ADDITIONAL_PROPERTIES_H_
