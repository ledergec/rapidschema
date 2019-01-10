//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef INCLUDE_RAPIDSCHEMA_OBJECT_H_
#define INCLUDE_RAPIDSCHEMA_OBJECT_H_

#include <string>
#include <unordered_set>
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

  GenericObject & operator= (const GenericObject & other) {
    if (this != &other) {
      mapping_initialized_ = false;
      name_config_mapping_ = std::map<std::basic_string<Ch>, const GenericConfig<Ch>*>();
    }
    return *this;
  }

  TransformResult Parse(const rapidjson::Value & document) override {
    UpdateMapping();

    if (document.IsObject() == false) {
      return TransformResult(Failure(fmt::format("Expected object but was: {} ",
                                          JsonTypeToString(document.GetType()))));
    }

    TransformResult result;
    for (auto pair : name_config_mapping_) {
      if (document.HasMember(pair.first.c_str()) == false) {
        auto tmp = pair.second->HandleMissing();
        tmp.AddPath(pair.first);
        result.Append(tmp);
        continue;
      }

      auto tmp = const_cast<Config*>(pair.second)->Parse(document.FindMember(pair.first.c_str())->value);
      if (tmp.Success() == false) {
        tmp.AddPath(pair.first);
        result.Append(tmp);
      }
    }

    return result;
  }

  TransformResult Validate() const override {
    UpdateMapping();

    TransformResult result;
    for (auto pair : name_config_mapping_) {
      result.Append(pair.second->Validate());
    }

    return result;
  }

  void Serialize(AbstractWriter<Ch>* writer) const override {
    UpdateMapping();

    writer->StartObject();
    for (const auto & pair : name_config_mapping_) {
      writer->Key(pair.first.c_str());
      pair.second->Serialize(writer);
    }
    writer->EndObject();
  }

  virtual TransformResult HandleUnexpectedMember(const std::basic_string<Ch>& key) {
    return TransformResult();
  }

  TransformResult HandleMissing() const override {
    return FailResult("Object is missing in config.");
  }

 protected:
  virtual std::map<std::basic_string<Ch>, const GenericConfig<Ch>*> CreateMemberMapping() const = 0;

 private:
  void UpdateMapping() const {
    if (mapping_initialized_ == false) {
      name_config_mapping_ = CreateMemberMapping();
      mapping_initialized_ = true;
    }
  }

  mutable bool mapping_initialized_;
  mutable std::map<std::basic_string<Ch>, const GenericConfig<Ch>*> name_config_mapping_;
};

using Object = GenericObject<>;

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_OBJECT_H_
