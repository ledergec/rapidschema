//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef RAPIDJSON_CONFIGNODE_H
#define RAPIDJSON_CONFIGNODE_H

#include <string>
#include <vector>

#include <fmt/format.h>

#include "config.h"
#include "rapidjson_type_to_string.h"
#include "transform_result.h"

namespace rapidoson {

    class ConfigNode : public Config {
    public:
        ConfigNode(const std::string& name, const std::vector<Config*>& sub_configs)
                : Config(name)
                , sub_configs_(sub_configs) {}

        TransformResult Parse(const rapidjson::Value & document) override {
            if (document.IsObject() == false) {
                TransformResult(Failure(fmt::format("Expected object but was: {} ",
                        JsonTypeToString(document.GetType()))));
            }

            TransformResult result;
            for (auto config : sub_configs_) {
                if (document.HasMember(config->GetName().c_str()) == false) {
                    result.Append(Failure(fmt::format("Missing member {}", config->GetName())));
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

    private:
        std::vector<Config*> sub_configs_;
    };

}  // rapidjson

#endif //RAPIDJSON_CONFIGVALUE_H
