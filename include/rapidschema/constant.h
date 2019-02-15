// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_DEFAULT_VALUE_H_
#define INCLUDE_RAPIDSCHEMA_DEFAULT_VALUE_H_

#include "rapidschema/value.h"
#include "rapidschema/result.h"

namespace rapidschema {

template<typename Ch, typename T>
class GenericConstant : public GenericValue<Ch, T> {
 public:
  using GenericValue<Ch, T>::operator=;

  void SetExpectedValue(const T& expected_value) {
    expected_value_ = expected_value;
  }

  const T& GetExpectedValue() const {
    return this->t_;
  }

  Result Transform(const rapidjson::Value& document) override {
    auto result = GenericValue<Ch, T>::Transform(document);
    if (result.Success()) {
      return Validate();
    } else {
      return result;
    }
  }

  Result Validate() const override {
    if (this->t_ == expected_value_) {
      return Result();
    } else {
      return FailResult(fmt::format("Expected constant value: {}, actual: {}.", expected_value_, this->t_));
    }
  }

 private:
  T expected_value_;
};

template <typename T>
using Constant = GenericConstant<char, T>;

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_DEFAULT_VALUE_H_
