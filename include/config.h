//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef RAPIDSCHEMA_CONFIG_H
#define RAPIDSCHEMA_CONFIG_H

#include <optional>
#include <string>

#include "rapidjson/document.h"
#include "transform_result.h"

namespace rapidschema {

    class Config {
    public:
        Config()
                : name_("") {}

        Config(const std::string &name)
                : name_(name) {}

        virtual ~Config() = default;

        virtual TransformResult Parse(const rapidjson::Value &document) = 0;

        virtual TransformResult Validate() const = 0;

        const std::string &GetName() {
            return name_;
        }

        void SetName(const std::string &name) {
            name_ = name;
        }

    private:
        std::string name_;
    };

}  // rapidjson

#endif //RAPIDSCHEMA_CONFIG_H
