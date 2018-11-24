//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef RAPIDJSON_CONFIG_H
#define RAPIDJSON_CONFIG_H

#include <optional>
#include <string>

#include "rapidjson/document.h"
#include "failure_collection.h"

namespace rapidoson {

    class Config {
    public:
        Config()
                : name_("") {}

        Config(const std::string &name)
                : name_(name) {}

        virtual ~Config() = default;

        virtual std::optional<FailureCollection> Parse(const rapidjson::Value &document) = 0;

        virtual std::optional<FailureCollection> Validate() const = 0;

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

#endif //RAPIDJSON_CONFIG_H
