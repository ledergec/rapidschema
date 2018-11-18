//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef RAPIDJSON_CONFIG_H
#define RAPIDJSON_CONFIG_H

#include <string>

#include "rapidjson/document.h"
#include "transformresult.h"

namespace rapidjson {

    class Config {
    public:
        Config(const std::string& name)
                : name_(name) {}

        virtual ~Config() = default;
        virtual TransformResult Parse(const Value& document) {
            auto res = ParseInternal(document);
            return AugmentResult(res);
        }

        virtual TransformResult Validate() const {
            auto res = ValidateInternal();
            return AugmentResult(res);
        }

        const std::string& GetName() {
            return name_;
        }

    protected:
        virtual TransformResult ParseInternal(const Value& document) = 0;
        virtual TransformResult ValidateInternal() const = 0;
    private:
        TransformResult AugmentResult(TransformResult &res) const {
            if (res.GetPath().empty()) {
                return TransformResult(res.Success(), name_, res.GetMessage());
            }
            return TransformResult(res.Success(),
                                   std::string(name_).append(".").append(res.GetPath()), res.GetMessage());
        }

        std::string name_;
    };

}  // rapidjson

#endif //RAPIDJSON_CONFIG_H
