// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_VALUE_H_
#define INCLUDE_RAPIDSCHEMA_VALUE_H_

#include <optional>
#include <string>

#include <fmt/format.h>

#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

#include "rapidschema/combined_constraint.h"
#include "rapidschema/concepts/requires_macro.h"
#include "rapidschema/concepts/correct_value_parameters.h"
#include "rapidschema/config.h"
#include "rapidschema/transform_result.h"
#include "rapidschema/type_properties.h"

namespace rapidschema {

template<typename Ch, typename T, template<typename> class ... Constraints>
    RAPIDSCHEMA_REQUIRES((CorrectValueParameters<T, Constraints...>))
class GenericValue;

template<typename T, template<typename> class ... Constraints>
    RAPIDSCHEMA_REQUIRES((CorrectValueParameters<T, Constraints...>))
GenericValue<char, T, Constraints...>
    MakeUtf8Value(Constraints<T>&&... constraints);

template<typename Ch, typename T, template<typename> class ... Constraints>
    RAPIDSCHEMA_REQUIRES((CorrectValueParameters<T, Constraints...>))
class GenericValue : public GenericConfig<Ch> {
 private:
  using ValueChecker = CombinedConstraint<T, Constraints...>;

 public:
  GenericValue() = default;

  GenericValue(const T& t) {  // NOLINT[runtime/explicit]
    t_ = t;
  }

  using CharType = Ch;
  using Type = T;

  GenericValue<Ch, T, Constraints...>& operator=(const T& t) {
    t_ = t;
    return *this;
  }

  operator T() {
    return t_;
  }

  const T& Get() const {
    return t_;
  }

  template <template<typename> class Constraint>
  Constraint<T> & GetConstraint() {
    return checker_.template Get<Constraint>();
  }

  TransformResult Parse(const rapidjson::Value& document) override {
    if (TypeProperties<T>::IsType(document) == false) {
      rapidjson::StringBuffer buffer;
      rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
      document.Accept(writer);
      return FailResult(
          fmt::format("Expected type: {}. Actual value was: {}", TypeProperties<T>::name, buffer.GetString()));
    }

    t_ = TypeProperties<T>::FromJson(document);

    return TransformResult();
  }

  TransformResult Validate() const override {
    return checker_.Check(t_);
  }

  void Serialize(AbstractWriter<Ch>* writer) const override {
    TypeProperties<T>::template Serialize<Ch>(t_, writer);
  }

  TransformResult HandleMissing() const override {
    return FailResult(fmt::format("Value of type {} is missing", TypeProperties<T>::name));
  }

 private:
  explicit GenericValue(ValueChecker&& checker)
      : checker_(std::forward<ValueChecker>(checker)) {}

  T t_;
  ValueChecker checker_;

  friend GenericValue MakeUtf8Value<T, Constraints...>(Constraints<T>&&... constraints);
};

template <typename T, template<typename> class ... Constraints>
using Value = GenericValue<char, T, Constraints...>;

template<typename T, template<typename> class ... Constraints>
    RAPIDSCHEMA_REQUIRES((CorrectValueParameters<T, Constraints...>))
GenericValue<char, T, Constraints...>
    MakeUtf8Value(Constraints<T>&&... constraints) {
  return GenericValue<char, T, Constraints...>(MakeConstraint<T, Constraints...>(
      std::forward<Constraints<T>>(constraints)...));
}

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_VALUE_H_
