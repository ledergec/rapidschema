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
  GenericNode(const std::basic_string<Ch>& name, const std::vector<GenericConfig<Encoding>*>& sub_configs)
      : GenericConfig<Encoding>(name)
      , sub_configs_(sub_configs) {}

  TransformResult Parse(const rapidjson::Value & document) override {
    if (document.IsObject() == false) {
      TransformResult(Failure(fmt::format("Expected object but was: {} ",
                                          JsonTypeToString(document.GetType()))));
    }

    TransformResult result;
    for (auto config : sub_configs_) {
      if (document.HasMember(config->GetName().c_str()) == false) {
        result.Append(Failure(fmt::format("Missing member: \"{}\"", config->GetName())));
        continue;
      }

      auto tmp = config->Parse(document.FindMember(config->GetName().c_str())->value);
      if (tmp.Success() == false) {
        tmp.AddPath(config->GetName());
        result.Append(tmp);
      }
    }

    return result;
  }

  TransformResult Validate() const override {
    TransformResult result;
    for (auto config : sub_configs_) {
      result.Append(config->Validate());
    }

    return result;
  }

  void Serialize(WriterBase<Encoding>* writer) const override {
    writer->StartObject();
    for (const auto & sub_config : sub_configs_) {
      writer->Key(sub_config->GetName().c_str());
      sub_config->Serialize(writer);
    }
    writer->EndObject();
  }

 private:
  std::vector<GenericConfig<Encoding>*> sub_configs_;
};

using Node = GenericNode<>;

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_CONFIGNODE_H_
