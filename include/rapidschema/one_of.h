// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_ONE_OF_H_
#define INCLUDE_RAPIDSCHEMA_ONE_OF_H_

#include <assert.h>
#include <functional>
#include <string>
#include <tuple>
#include <utility>

#include "rapidschema/concepts/correct_value_parameters.h"
#include "rapidschema/concepts/requires_macro.h"
#include "rapidschema/concepts/unique_json_types.h"
#include "rapidschema/meta/json_type_set.h"
#include "rapidschema/meta/unique_tuple.h"
#include "rapidschema/rapidjson_type_to_string.h"
#include "rapidschema/value.h"

namespace rapidschema {

namespace internal {

template<typename Config>
struct ConfigHasSameType {
  template<typename OtherConfig>
  using Condition = std::is_same<Config, OtherConfig>;
};

}  // namespace internal

template<typename Encoding, typename... Configs> RAPIDSCHEMA_REQUIRES(UniqueTypes<typename Configs...>)
class GenericOneOf;

template<typename... Configs> RAPIDSCHEMA_REQUIRES(UniqueTypes<typename Configs...>)
GenericOneOf<char, Configs...> MakeOneOf(Configs&&... configs);

template<typename Ch, typename... Configs> RAPIDSCHEMA_REQUIRES(UniqueTypes<typename Configs...>)
class GenericOneOf : public GenericConfig<Ch> {
 private:
  using Tuple = internal::UniqueTuple<Configs...>;

  static constexpr int INVALID_ONE_OF_INDEX = -1;

 public:
  GenericOneOf() = default;

  template <typename Config>
  explicit GenericOneOf(const Config& config) {
    SetVariant<Config>(config);
    SelectVariant<Config>();
  }

  Result Transform(const rapidjson::Value& document) override {
    size_t n_matches = 0;
    Result result;
    for (size_t i = 0; i < unique_tuple_.Size(); i++) {
      auto tmp_result = unique_tuple_.template Get<GenericConfig<Ch>>(i)->Transform(document);
      if (tmp_result.Success()) {
        one_of_index_ = i;
        n_matches++;
      }
      result.Append(tmp_result);
    }
    if (n_matches == 0) {
      one_of_index_ = INVALID_ONE_OF_INDEX;
      Result failed_result =
          FailResult(fmt::format("No type in OneOf matched for the following {} reasons:", unique_tuple_.Size()));
      failed_result.Append(result);
      return failed_result;
    } else if (n_matches > 1) {
      return FailResult("Multiple matches - ambiguous result.");
    }
    return Result();
  }

  template <typename Config>
  using ConfigOf =
      typename Tuple::template ElementWithCondition<internal::ConfigHasSameType<Config>::template Condition>;

  template <typename Config>
  GenericOneOf<Ch, Configs...>& operator=(const Config& config) {
    one_of_index_ = ConfigOf<Config>::Index;
    GetVariant<Config>() = config;
    return *this;
  }

  template <typename Config>
  const Config& GetVariant() const {
    return unique_tuple_.template GetIfCondition<internal::ConfigHasSameType<Config>::template Condition>();
  }

  template <typename Config>
  Config& GetVariant() {
    return unique_tuple_.template GetIfCondition<internal::ConfigHasSameType<Config>::template Condition>();
  }

  template <typename Config>
  void SetVariant(const Config& config) {
    unique_tuple_.template GetIfCondition<internal::ConfigHasSameType<Config>::template Condition>() = config;
  }

  template <typename Config>
  void SelectVariant() {
    one_of_index_ = unique_tuple_.template IndexOf<internal::ConfigHasSameType<Config>::template Condition>();
  }

  template <typename Config>
  bool Is() {
    return ConfigOf<Config>::Index == one_of_index_;
  }

  Result Validate() const override {
    assert(one_of_index_ != INVALID_ONE_OF_INDEX);
    return unique_tuple_.template Get<Config>(one_of_index_)->Validate();
  }

  void Serialize(AbstractWriter<Ch>* writer) const override {
    return unique_tuple_.template Get<Config>(one_of_index_)->Serialize(writer);
  }

  bool IsRequired() const override {
    return true;
  }

 private:
  int32_t one_of_index_ = INVALID_ONE_OF_INDEX;
  // must be a tuple because each config and its constraints must be stored
  Tuple unique_tuple_;

  explicit GenericOneOf(Tuple&& data)
      : unique_tuple_(std::forward<Tuple>(data)) {}

  friend GenericOneOf<Ch, Configs...> MakeOneOf<Configs...>(Configs&&... configs);
};

template <typename... Configs>
using OneOf = GenericOneOf<char, Configs...>;

template<typename... Configs> RAPIDSCHEMA_REQUIRES(UniqueTypes<Configs...>)
OneOf<Configs...> MakeOneOf(Configs&&... configs) {
  return OneOf<Configs...>(
      internal::UniqueTuple<Configs...>(
          std::make_tuple<Configs...>(std::forward<Configs>(configs)...)));
}

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_ONE_OF_H_
