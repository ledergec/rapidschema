// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_OPTIONAL_CONFIG_H_
#define INCLUDE_RAPIDSCHEMA_OPTIONAL_CONFIG_H_

#include "rapidschema/config.h"
#include "rapidschema/transform_result.h"

namespace rapidschema {

template<typename BaseConfig>
class OptionalConfig : public GenericConfig<typename BaseConfig::CharType> {
 public:
  TransformResult Transform(const rapidjson::Value &document) override {
    if (HasValue() == false) {
      optional_config_ = BaseConfig();
    }
    return optional_config_.value().Transform(document);
  }

  TransformResult Validate() const override {
    if (HasValue()) {
      return optional_config_.value().Validate();
    } else {
      return TransformResult();
    }
  }

  TransformResult HandleMissing() const override {
    return TransformResult();
  }

  void Serialize(AbstractWriter<typename BaseConfig::CharType>* writer) const override {
    if (HasValue()) {
      optional_config_.value().Serialize(writer);
    }
  }

  void CollectMemory() const override {
    if (HasValue()) {
      optional_config_.value().CollectMemory();
    }
  }

  bool HasValue() const {
    return optional_config_.has_value();
  }

  const BaseConfig & GetValue() const {
    assert(HasValue());
    return optional_config_.value();
  }

  BaseConfig & GetValue() {
    assert(HasValue());
    return optional_config_.value();
  }

  OptionalConfig<BaseConfig>& operator=(const std::optional<BaseConfig> & optional_config) {
    optional_config_ = optional_config;
    return *this;
  }

 private:
  std::optional<BaseConfig> optional_config_;
};

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_OPTIONAL_CONFIG_H_
