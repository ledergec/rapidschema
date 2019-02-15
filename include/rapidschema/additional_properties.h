// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_ADDITIONAL_PROPERTIES_H_
#define INCLUDE_RAPIDSCHEMA_ADDITIONAL_PROPERTIES_H_

#include "rapidschema/result.h"

namespace rapidschema {

template<typename BaseObject>
class AdditionalProperties : public BaseObject {
 public:
  Result HandleUnexpectedMember(const std::basic_string<typename BaseObject::CharType>& key) override {
    return Result();
  }
};

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_ADDITIONAL_PROPERTIES_H_
