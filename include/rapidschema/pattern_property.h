// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_PATTERN_PROPERTY_H_
#define INCLUDE_RAPIDSCHEMA_PATTERN_PROPERTY_H_

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

  explicit PatternProperty(const StringType& pattern)
      : pattern_(pattern)
      , regex_(Regex<CharType>::CreateRegex(pattern)) {}

  explicit PatternProperty(const typename Regex<CharType>::RegexType& pattern)
      : regex_(pattern) {}

  virtual ~PatternProperty() = default;

  const StringType & GetPattern() const override {
    return pattern_;
  }

  bool IsMatchingName(const StringType & name) const override {
    return Regex<CharType>::IsCompleteMatch(regex_, name);
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

  Result Transform(const StringType& name, const rapidjson::Value& document) override {
    assert(IsMatchingName(name));
    ConfigType config;
    auto result = config.Transform(document);
    if (result.Success()) {
      Insert(name, config);
      return result;
    } else {
      result.AddPath(name);
      return result;
    }
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

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION
  std::shared_ptr<schema::SubSchema> CreateSchema(const schema::SchemaAssemblerInterface & assembler) const override {
    return ConfigType().CreateSchema(assembler);
  }
#endif

 private:
  StringType pattern_;
  std::basic_regex<CharType> regex_;
  std::unordered_map<StringType, ConfigType> properties_;
};

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_PATTERN_PROPERTY_H_
