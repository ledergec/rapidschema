//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef RAPIDJSON_CONFIGVALUE_H
#define RAPIDJSON_CONFIGVALUE_H

#include <string>

#include "combined_constraint.h"
#include "config.h"
#include "valueparser.h"

namespace rapidjson {

    namespace internal {
        template<typename ValueType>
        struct TypeHelper<ValueType, std::string> {

            static bool Is(const ValueType &v) { return v.IsString(); }

            static std::string Get(const ValueType &v) { return v.GetString(); }

            static ValueType &Set(ValueType &v, const std::string data) {
                return v.SetString(typename ValueType::StringRefType(data));
            }

            static ValueType &Set(ValueType &v, const std::string data, typename ValueType::AllocatorType &a) {
                return v.SetString(data, a);
            }
        };
    }

    template<typename T, typename ...Constraints>
    class ConfigValue : public Config {
    public:
        ConfigValue(const std::string& name)
                : Config(name) {}

        operator T() {
            return t_;
        }

        const T& Get() {
            return t_;
        }

    protected:
        TransformResult ParseInternal(const Value& document) override {
            if (document.Is<T>() == false) {
                return TransformResult(false, GetName(), std::string("Unexpected type ").append(TypeToString(document.GetType())));
            }

            t_ = document.Get<T>();

            return TransformResult::TRUE;
        }

        TransformResult ValidateInternal() const override {
            return CombinedConstraint<T, Constraints...>::Check(t_);
        }

    private:
        T t_;
    };

}  // rapidjson

#endif //RAPIDJSON_CONFIGVALUE_H
