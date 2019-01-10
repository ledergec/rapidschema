//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef INCLUDE_RAPIDSCHEMA_ADDITIONAL_PROPERTIES_H_
#define INCLUDE_RAPIDSCHEMA_ADDITIONAL_PROPERTIES_H_

#include "rapidschema/transform_result.h"

namespace rapidschema {

template<typename BaseObject>
class AdditionalProperties : public BaseObject {
 public:
  TransformResult HandleUnexpectedMember(const std::basic_string<typename BaseObject::CharType>& key) override {
    return TransformResult();
  }
};

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_ADDITIONAL_PROPERTIES_H_
