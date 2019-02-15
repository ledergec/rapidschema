// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_OBJECT_H_
#define INCLUDE_RAPIDSCHEMA_OBJECT_H_

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>

#include <fmt/format.h>

#include "rapidschema/config.h"
#include "rapidschema/rapidjson_type_to_string.h"
#include "rapidschema/transform_result.h"

namespace rapidschema {

template<typename Ch = char>
class GenericObject : public GenericConfig<Ch> {
 public:
  using CharType = Ch;

  GenericObject()
    : mapping_initialized_(false) {}

  GenericObject(const GenericObject<Ch>& other)
    : mapping_initialized_(false) {}

  GenericObject(GenericObject<Ch>&& other)
      : mapping_initialized_(false) {}

  GenericObject& operator= (const GenericObject& other) {
    if (this != &other) {
      mapping_initialized_ = false;
      name_config_mapping_ = std::map<std::basic_string<Ch>, const GenericConfig<Ch>*>();
    }
    return *this;
  }

  Result Transform(const rapidjson::Value& document) override {
    UpdateMapping();

    if (document.IsObject() == false) {
      return Result(Failure(fmt::format("Expected object but was: {} ",
                                          JsonTypeToString(document.GetType()))));
    }

    Result result;
    int missing_count = 0;
    for (auto pair : name_config_mapping_) {
      if (document.HasMember(pair.first.c_str()) == false) {
        auto tmp = pair.second->HandleMissing();
        tmp.AddPath(pair.first);
        result.Append(tmp);
        missing_count++;
        continue;
      }

      auto tmp = const_cast<Config*>(pair.second)->Transform(document.FindMember(pair.first.c_str())->value);
      if (tmp.Success() == false) {
        tmp.AddPath(pair.first);
        result.Append(tmp);
      }
    }

    if (document.MemberCount() + missing_count > name_config_mapping_.size()) {
      auto member_it = document.MemberBegin();
      while (member_it != document.MemberEnd()) {
        auto name = std::basic_string<Ch>(member_it->name.GetString(), member_it->name.GetStringLength());
        if (name_config_mapping_.find(name) == name_config_mapping_.end()) {
          result.Append(HandleUnexpectedMember(name));
        }
        member_it++;
      }
    }
    return result;
  }

  Result Validate() const override {
    UpdateMapping();

    Result result;
    for (auto pair : name_config_mapping_) {
      auto tmp = pair.second->Validate();
      tmp.AddPath(pair.first);
      result.Append(tmp);
    }

    return result;
  }

  void Serialize(AbstractWriter<Ch>* writer) const override {
    auto pair_list = CreateMemberMapping();

    writer->StartObject();
    for (const auto& pair : pair_list) {
      writer->Key(pair.first.c_str());
      pair.second->Serialize(writer);
    }
    writer->EndObject();
  }

  virtual Result HandleUnexpectedMember(const std::basic_string<Ch>& key) {
    return Result();
  }

  Result HandleMissing() const override {
    return FailResult("Object is missing in config.");
  }

  void CollectMemory() const override {
    if (mapping_initialized_) {
      for (const auto& pair : name_config_mapping_) {
        pair.second->CollectMemory();
      }

      mapping_initialized_ = false;
      name_config_mapping_.clear();
    }
  }

 protected:
  virtual std::vector<std::pair<std::basic_string<Ch>, const GenericConfig<Ch>*>> CreateMemberMapping() const = 0;

 private:
  void UpdateMapping() const {
    if (mapping_initialized_ == false) {
      name_config_mapping_ = std::unordered_map<std::string, const Config*>();
      auto list = CreateMemberMapping();
      for (const auto pair : list) {
          name_config_mapping_.insert(pair);
      }
      mapping_initialized_ = true;
    }
  }

  mutable bool mapping_initialized_;
  mutable std::unordered_map<std::basic_string<Ch>, const GenericConfig<Ch>*> name_config_mapping_;
};

using Object = GenericObject<>;

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_OBJECT_H_
