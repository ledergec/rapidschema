//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef INCLUDE_RAPIDSCHEMA_CONFIGVALUE_H_
#define INCLUDE_RAPIDSCHEMA_CONFIGVALUE_H_

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

template<typename Encoding, typename T, template<typename> class ... Constraints>
    RAPIDSCHEMA_REQUIRES((CorrectValueParameters<T, Constraints...>))
class GenericValue;

template<typename T, template<typename> class ... Constraints>
    RAPIDSCHEMA_REQUIRES((CorrectValueParameters<T, Constraints...>))
GenericValue<rapidjson::UTF8<>, T, Constraints...>
    MakeUtf8Value(const std::string& name, Constraints<T>&&... constraints);

template<typename Encoding, typename T, template<typename> class ... Constraints>
    RAPIDSCHEMA_REQUIRES((CorrectValueParameters<T, Constraints...>))
class GenericValue : public GenericConfig<Encoding> {
 protected:
  using Ch = typename Encoding::Ch;

 private:
  using ValueChecker = CombinedConstraint<T, Constraints...>;

 public:
  GenericValue() = default;

  explicit GenericValue(const std::basic_string<Ch>& name)
      : GenericConfig<Encoding>(name) {}

  using Type = T;

  GenericValue<Encoding, T, Constraints...>& operator=(const T& t) {
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

  void Serialize(AbstractWriter<Encoding>* writer) const override {
    TypeProperties<T>::Serialize(t_, writer);
  }

 private:
  GenericValue(const std::string& name, ValueChecker&& checker)
      : GenericConfig<Encoding>(name)
      , checker_(std::forward<ValueChecker>(checker)) {}

  T t_;
  ValueChecker checker_;

  friend GenericValue MakeUtf8Value<T, Constraints...>(const std::string& name, Constraints<T>&&... constraints);
};

template <typename T, template<typename> class ... Constraints>
using Value = GenericValue<rapidjson::UTF8<>, T, Constraints...>;

template<typename T, template<typename> class ... Constraints>
    RAPIDSCHEMA_REQUIRES((CorrectValueParameters<T, Constraints...>))
GenericValue<rapidjson::UTF8<>, T, Constraints...>
    MakeUtf8Value(const std::string& name, Constraints<T>&&... constraints) {
  return GenericValue<rapidjson::UTF8<>, T, Constraints...>(
      name, MakeConstraint<T, Constraints...>(std::forward<Constraints<T>>(constraints)...));
}

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_CONFIGVALUE_H_
