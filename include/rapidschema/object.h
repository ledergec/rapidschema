// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_OBJECT_H_
#define INCLUDE_RAPIDSCHEMA_OBJECT_H_

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>

#include <fmt/format.h>

#include "rapidschema/config.h"
#include "rapidschema/pattern_property.h"
#include "rapidschema/rapidjson_type_to_string.h"
#include "rapidschema/result.h"

namespace rapidschema {

template<typename Ch = char>
class GenericObject : public GenericConfig<Ch> {
 public:
  using PropertyMapping = std::vector<std::pair<std::basic_string<Ch>, const GenericConfig<Ch>*>>;
  using PatternPropertyList = std::vector<const PatternPropertyInterface<Ch>*>;

  GenericObject()
    : member_cache_initialized_(false) {}

  GenericObject(const GenericObject<Ch>& other)
    : member_cache_initialized_(false) {}

  GenericObject(GenericObject<Ch>&& other)
      : member_cache_initialized_(false) {}

  GenericObject& operator= (const GenericObject& other) {
    if (this != &other) {
      member_cache_initialized_ = false;
      properties_chache_.clear();
      pattern_properties_cache_.clear();
    }
    return *this;
  }

  Result Transform(const rapidjson::Value& document) override {
    UpdateMemberCache();

    if (document.IsObject() == false) {
      return Result(Failure(fmt::format("Expected object but was: {} ", JsonTypeToString(document.GetType()))));
    }

    Result result;
    size_t found_properties_count = 0;
    auto member_it = document.MemberBegin();
    while (member_it != document.MemberEnd()) {
      auto name = std::basic_string<Ch>(member_it->name.GetString(), member_it->name.GetStringLength());
      auto property = properties_chache_.find(name);
      if (property != properties_chache_.end()) {  // there is a property with the given name
        found_properties_count++;

        auto transform_result =
          const_cast<Config*>(property->second)->Transform(member_it->value);
        if (transform_result.Success() == false) {
          transform_result.AddPath(property->first);
          result.Append(transform_result);
        }
      }

      bool matching_pattern_property_found = false;
      for (auto& pattern_property : pattern_properties_cache_) {
        if (pattern_property->IsMatchingName(name)) {
          result.Append(const_cast<PatternPropertyInterface<Ch>*>(pattern_property)->Transform(name, member_it->value));
          matching_pattern_property_found = true;
        }
      }

      // no property or pattern property with the given name
      if (property == properties_chache_.end() && matching_pattern_property_found == false
          && AdditionalPropertiesAllowed() == false) {
        result.Append(Failure(fmt::format("Unexpected member encountered: {}", name)));
      }

      member_it++;
    }

    if (found_properties_count < properties_chache_.size()) {
      for (auto& pair : properties_chache_) {
        if (document.HasMember(pair.first.c_str()) == false && pair.second->IsRequired()) {
          result.Append(Failure(pair.first, "Is missing."));
          continue;
        }
      }
    }

    return result;
  }

  Result Validate() const override {
    UpdateMemberCache();

    Result result;
    for (const auto & pair : properties_chache_) {
      auto validation_result = pair.second->Validate();
      validation_result.AddPath(pair.first);
      result.Append(validation_result);
    }

    for (const auto & pattern_property : pattern_properties_cache_) {
      result.Append(pattern_property->Validate());
    }

    return result;
  }

  void Serialize(AbstractWriter<Ch>* writer) const override {
    auto pair_list = CreatePropertyMapping();
    UpdateMemberCache();

    writer->StartObject();
    for (const auto& pair : pair_list) {
      if (pair.second->IsPresent()) {
        writer->Key(pair.first.c_str());
        pair.second->Serialize(writer);
      }
    }

    for (const auto & pattern_property : pattern_properties_cache_) {
      pattern_property->Serialize(writer);
    }

    writer->EndObject();
  }

  virtual bool AdditionalPropertiesAllowed() const {
    return true;
  }

  bool IsRequired() const override {
    return true;
  }

  void CollectMemory() const override {
    if (member_cache_initialized_) {
      for (const auto & pair : properties_chache_) {
        pair.second->CollectMemory();
      }

      member_cache_initialized_ = false;
      properties_chache_.clear();
    }
  }

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION
  std::shared_ptr<schema::SubSchema> CreateSchema(const schema::SchemaAssemblerInterface & assembler) const override {
    auto pair_list = CreatePropertyMapping();
    UpdateMemberCache();

    auto object_schema = assembler.CreateObjectSchema();
    for (const auto pair : pair_list) {
      object_schema->AddProperty(pair.first, pair.second->CreateSchema(assembler));
      if (pair.second->IsRequired()) {
        object_schema->AddRequired(pair.first);
      }
    }

    for (const auto pattern_property : pattern_properties_cache_) {
      object_schema->AddPatternProperty(pattern_property->GetPattern(), pattern_property->CreateSchema(assembler));
    }

    if (AdditionalPropertiesAllowed() == false) {
      object_schema->SetAdditionalProperties(false);
    }

    return object_schema->CreateSubSchema();
  }
#endif

 protected:
  virtual PropertyMapping CreatePropertyMapping() const {
    return PropertyMapping();
  }

  virtual PatternPropertyList CreatePatternPropertyList() const {
    return PatternPropertyList();
  }

 private:
  void UpdateMemberCache() const {
    if (member_cache_initialized_ == false) {
      properties_chache_ = std::unordered_map<std::string, const Config*>();
      auto list = CreatePropertyMapping();
      for (const auto & pair : list) {
          properties_chache_.insert(pair);
      }
      pattern_properties_cache_ = CreatePatternPropertyList();
      member_cache_initialized_ = true;
    }
  }

  mutable bool member_cache_initialized_;
  mutable std::unordered_map<std::basic_string<Ch>, const GenericConfig<Ch>*> properties_chache_;
  mutable PatternPropertyList pattern_properties_cache_;
};

using Object = GenericObject<>;

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_OBJECT_H_
