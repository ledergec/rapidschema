// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_VARIANT_H_
#define INCLUDE_RAPIDSCHEMA_VARIANT_H_

#include <assert.h>
#include <functional>
#include <optional>
#include <string>
#include <tuple>
#include <utility>

#include "rapidschema/concepts/requires_macro.h"
#include "rapidschema/concepts/correct_value_parameters.h"
#include "rapidschema/concepts/unique_json_types.h"
#include "rapidschema/value.h"
#include "rapidschema/meta/json_type_set.h"
#include "rapidschema/meta/unique_tuple.h"
#include "rapidschema/rapidjson_type_to_string.h"

namespace rapidschema {

namespace internal {

template<typename T>
struct ConfigValueHasType {
  template<typename CV>
  using Condition = std::is_same<typename CV::Type, T>;
};

}  // namespace internal

template<typename Encoding, typename... Values> RAPIDSCHEMA_REQUIRES(UniqueJsonTypes<typename Values::Type...>)
class GenericVariant;

template<typename... Values> RAPIDSCHEMA_REQUIRES(UniqueJsonTypes<typename Values::Type...>)
GenericVariant<char, Values...> MakeUtf8Variant(Values&&... values);

template<typename Ch, typename... Values> RAPIDSCHEMA_REQUIRES(UniqueJsonTypes<typename Values::Type...>)
class GenericVariant : public GenericConfig<Ch> {
 private:
  using Tuple = internal::UniqueTuple<Values...>;

  template <typename T>
  using ConfigOf = typename Tuple::template ElementWithCondition<internal::ConfigValueHasType<T>::template Condition>;

  template <typename T>
  using ConfigTypeOf = typename ConfigOf<T>::Type;

  template <typename T>
  static constexpr size_t ConfigIndexOf = ConfigOf<T>::Index;

  static constexpr int INVALID_VARIANT_INDEX = -1;

 public:
  GenericVariant() = default;

  TransformResult Parse(const rapidjson::Value& document) override {
    variant_index_ = unique_tuple_.ApplyUntilSuccess(
        [&document](auto& config_value) {
          return config_value.Parse(document).Success();
        });
    if (variant_index_ == -1) {
      variant_index_ = INVALID_VARIANT_INDEX;
      return FailResult(fmt::format(
          "No type in variant matched. Actual type: {}",
          JsonTypeToString(document.GetType())));
    }
    return TransformResult();
  }

  template <typename T>
  GenericVariant<Ch, Values...>& operator=(const T& t) {
    variant_index_ = ConfigIndexOf<T>;
    GetVariant<T>() = t;
    return *this;
  }

  template <typename T>
  const ConfigTypeOf<T>& GetVariant() const {
    return unique_tuple_.template GetIfCondition<internal::ConfigValueHasType<T>::template Condition>();
  }

  template <typename T>
  ConfigTypeOf<T> & GetVariant() {
    return unique_tuple_.template GetIfCondition<internal::ConfigValueHasType<T>::template Condition>();
  }

  template <typename T>
  void SetVariant(const T& t) {
    unique_tuple_.template GetIfCondition<internal::ConfigValueHasType<T>::template Condition>() = t;
    variant_index_ = unique_tuple_.template IndexOf<internal::ConfigValueHasType<T>::template Condition>();
  }

  template <typename T>
  bool Is() {
    return ConfigIndexOf<T> == variant_index_;
  }

  TransformResult Validate() const override {
    assert(variant_index_ != INVALID_VARIANT_INDEX);
    return unique_tuple_.template Get<Config>(variant_index_)->Validate();
  }

  void Serialize(AbstractWriter<Ch>* writer) const override {
    return unique_tuple_.template Get<Config>(variant_index_)->Serialize(writer);
  }

  TransformResult HandleMissing() const {
    return FailResult("is missing");
  }

 private:
  int32_t variant_index_ = INVALID_VARIANT_INDEX;
  // must be a tuple because each config value and its constraints must be stored
  Tuple unique_tuple_;

  explicit GenericVariant(Tuple&& data)
      : unique_tuple_(std::forward<Tuple>(data)) {}

  friend GenericVariant<Ch, Values...> MakeUtf8Variant<Values...>(Values&&... values);
};

template <typename... Values>
using Variant = GenericVariant<char, Values...>;

template<typename... Values> RAPIDSCHEMA_REQUIRES(UniqueJsonTypes<typename Values::Type...>)
Variant<Values...> MakeUtf8Variant(Values&&... values) {
  return Variant<Values...>(
      internal::UniqueTuple<Values...>(
          std::make_tuple<Values...>(std::forward<Values>(values)...)));
}

template<typename T, template<typename> class ... Constraints>
    RAPIDSCHEMA_REQUIRES((CorrectValueParameters<T, Constraints...>))
Value<T, Constraints...> MakeUtf8VariantValue(Constraints<T>&&... constraints) {
  return MakeUtf8Value<T, Constraints...>(std::forward<Constraints<T>>(constraints)...);
}

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_VARIANT_H_
