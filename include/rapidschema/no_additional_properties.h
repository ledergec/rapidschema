// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_NO_ADDITIONAL_PROPERTIES_H_
#define INCLUDE_RAPIDSCHEMA_NO_ADDITIONAL_PROPERTIES_H_

#include <fmt/format.h>

#include "rapidschema/transform_result.h"

namespace rapidschema {

template<typename BaseObject>
class NoAdditionalProperties : public BaseObject {
 public:
  Result HandleUnexpectedMember(const std::basic_string<typename BaseObject::CharType>& key) override {
    return FailResult(fmt::format("Unexpected member encountered: {}", key));
  }
};

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_NO_ADDITIONAL_PROPERTIES_H_
