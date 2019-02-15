// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_PATTERN_PROPERTY_H_
#define INCLUDE_PATTERN_PROPERTY_H_

#include <assert.h>

#include <string>
#include <unordered_map>

#include <rapidjson/document.h>

#include "rapidschema/pattern_property_interface.h"
#include "rapidschema/result.h"
#include "rapidschema/utils/regex.h"

namespace rapidschema {

template<typename ConfigType>
class PatternProperty : public PatternPropertyInterface<typename ConfigType::CharType> {
 public:
  using CharType = typename PatternPropertyInterface<typename ConfigType::CharType>::CharType;
  using StringType = typename PatternPropertyInterface<typename ConfigType::CharType>::StringType;

  PatternProperty(const StringType& pattern)
      : pattern_(Regex<CharType>::CreateRegex(pattern)) {}

  bool IsMatchingName(const StringType & name) const override {
    return Regex<CharType>::IsCompleteMatch(pattern_, name);
  }

  void Insert(const StringType & name, const ConfigType & config) {
    assert(IsMatchingName(name));
    properties_.insert(std::make_pair(name, config));
  }

  void Remove(const StringType & name) {
    properties_.erase(name);
  }

  const std::unordered_map<StringType, ConfigType> GetProperties() const {
    return properties_;
  }

  Result Transform(StringType& name, const rapidjson::Value& document) override {
    assert(IsMatchingName(name));
    ConfigType config;
    auto result = config.Transform(document);
    if (result.Success()) {
      Insert(name, config);
    }
    return result;
  }

  Result Validate() const override {
    Result result;
    for (const auto & pair : properties_) {
      auto validate_result = pair.second.Validate();
      validate_result.AddPath(pair.first);
      result.Append(validate_result);
    }
    return result;
  }

  void Serialize(AbstractWriter<CharType>* writer) const override {
    for (const auto & pair : properties_) {
      writer->Key(pair.first);
      pair.second.Serialize(writer);
    }
  }

 private:
  std::basic_regex<CharType> pattern_;
  std::unordered_map<StringType, ConfigType> properties_;
};

}  // namespace rapidschema

#endif  // INCLUDE_PATTERN_PROPERTY_H_
