//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef INCLUDE_RAPIDSCHEMA_CONFIGNODE_H_
#define INCLUDE_RAPIDSCHEMA_CONFIGNODE_H_

#include <string>
#include <vector>

#include <fmt/format.h>

#include "rapidschema/config.h"
#include "rapidschema/rapidjson_type_to_string.h"
#include "rapidschema/transform_result.h"

namespace rapidschema {

template<typename Encoding = rapidjson::UTF8<>>
class GenericNode : public GenericConfig<Encoding> {
  using Ch = typename Encoding::Ch;

 public:
  GenericNode()
    : mapping_initialized_(false) {}

  GenericNode(const GenericNode<Encoding>& other)
    : mapping_initialized_(false) {}

  GenericNode(GenericNode<Encoding>&& other)
      : mapping_initialized_(false) {}

  GenericNode & operator= (const GenericNode & other) {
    if (this != &other) {
      mapping_initialized_ = false;
      name_config_mapping_ = std::map<std::string, const GenericConfig<Encoding>*>();
    }
    return *this;
  }

  TransformResult Parse(AbstractReader<Encoding> * reader) override {
    assert(false);
    return TransformResult();
  }

  TransformResult Parse(const rapidjson::Value & document) override {
    UpdateMapping();

    if (document.IsObject() == false) {
      TransformResult(Failure(fmt::format("Expected object but was: {} ",
                                          JsonTypeToString(document.GetType()))));
    }

    TransformResult result;
    for (auto pair : name_config_mapping_) {
      if (document.HasMember(pair.first.c_str()) == false) {
        result.Append(Failure(fmt::format("Missing member: \"{}\"", pair.first)));
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

  void Serialize(AbstractWriter<Encoding>* writer) const override {
    UpdateMapping();

    writer->StartObject();
    for (const auto & pair : name_config_mapping_) {
      writer->Key(pair.first.c_str());
      pair.second->Serialize(writer);
    }
    writer->EndObject();
  }

 protected:
  virtual std::map<std::string, const GenericConfig<Encoding>*> CreateMemberMapping() const = 0;

 private:
  void UpdateMapping() const {
    if (mapping_initialized_ == false) {
      name_config_mapping_ = CreateMemberMapping();
      mapping_initialized_ = true;
    }
  }

  mutable bool mapping_initialized_;
  // TODO(cledergerber) should be std::basic_string<Ch> not std::string.
  mutable std::map<std::string, const GenericConfig<Encoding>*> name_config_mapping_;
};

using Node = GenericNode<>;

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_CONFIGNODE_H_
