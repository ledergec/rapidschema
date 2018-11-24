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

namespace rapidoson {

    class ConfigNode : public Config {
    public:
        ConfigNode(const std::string& name, const std::vector<Config*>& sub_configs)
                : Config(name)
                , sub_configs_(sub_configs) {}

    protected:
        FailureCollection ParseInternal(const rapidjson::Value & document) override {
            if (document.IsObject() == false) {
                return FailureCollection(false, GetName(), fmt::format("Expected object but was: {} ",
                        JsonTypeToString(document.GetType())));
            }

            for (auto config : sub_configs_) {
                if (document.HasMember(config->GetName().c_str()) == false) {
                    return FailureCollection(false, "", std::string("Missing member ").append(config->GetName()));
                }

                auto result = config->Parse(document.FindMember(config->GetName().c_str())->value);
                if (result.Success() == false) {
                    return result;
                }
            }

            return FailureCollection::FailureCollection();
        }

        FailureCollection ValidateInternal() const override {
            for (auto config : sub_configs_) {
                auto result = config->Validate();
                if (result.Success() == false) {
                    return result;
                }
            }

            return FailureCollection::FailureCollection();
        }

    private:
        std::vector<Config*> sub_configs_;
    };

}  // rapidjson

#endif //RAPIDJSON_CONFIGVALUE_H
