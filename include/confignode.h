//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef RAPIDJSON_CONFIGNODE_H
#define RAPIDJSON_CONFIGNODE_H

#include <string>
#include <vector>

#include "config.h"
#include "valueparser.h"

namespace rapidjson {

    class ConfigNode : public Config {
    public:
        ConfigNode(const std::string& name, const std::vector<Config*>& sub_configs)
                : Config(name)
                , sub_configs_(sub_configs) {}

    protected:
        TransformResult ParseInternal(const Value & document) override {
            if (document.IsObject() == false) {
                return TransformResult(false, GetName(), std::string("Unexpected type ").append(TypeToString(document.GetType())));
            }

            for (auto config : sub_configs_) {
                if (document.HasMember(config->GetName().c_str()) == false) {
                    return TransformResult(false, "", std::string("Missing member ").append(config->GetName()));
                }

                auto result = config->Parse(document.FindMember(config->GetName().c_str())->value);
                if (result.Success() == false) {
                    return result;
                }
            }

            return TransformResult::TRUE;
        }

        TransformResult ValidateInternal() const override {
            for (auto config : sub_configs_) {
                auto result = config->Validate();
                if (result.Success() == false) {
                    return result;
                }
            }

            return TransformResult::TRUE;
        }

    private:
        std::vector<Config*> sub_configs_;
    };

}  // rapidjson

#endif //RAPIDJSON_CONFIGVALUE_H
