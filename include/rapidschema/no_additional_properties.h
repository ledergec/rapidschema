//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef INCLUDE_RAPIDSCHEMA_NO_ADDITIONAL_PROPERTIES_H_
#define INCLUDE_RAPIDSCHEMA_NO_ADDITIONAL_PROPERTIES_H_

#include <fmt/format.h>

namespace rapidschema {

template<typename BaseObject>
class NoAdditionalProperties : public BaseObject {
 public:
  TransformResult HandleUnexpectedMember(const std::basic_string<typename BaseObject::CharType>& key) override {
    return FailResult(fmt::format("Unexpected member encountered: {}", key));
  }
};

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_NO_ADDITIONAL_PROPERTIES_H_
