//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef RAPIDJSON_CONFIGVALUE_H
#define RAPIDJSON_CONFIGVALUE_H

#include <optional>
#include <string>

#include <fmt/format.h>

#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

#include "combined_constraint.h"
#include "config.h"
#include "rapidjson_type_to_string.h"
#include "transform_result.h"
#include "type_name.h"

namespace rapidjson {
    namespace internal {
        template<typename ValueType>
        struct TypeHelper<ValueType, std::string> {

            static bool Is(const ValueType& v) { return v.IsString(); }

            static std::string Get(const ValueType& v) { return v.GetString(); }

            static ValueType& Set(ValueType& v, const std::string data) {
                return v.SetString(typename ValueType::StringRefType(data));
            }

            static ValueType& Set(ValueType& v, const std::string data, typename ValueType::AllocatorType &a) {
                return v.SetString(data, a);
            }
        };
    }
}

namespace rapidoson {

    template<typename T, template<typename> class ... Constraints>
    class ConfigValue;

    template<typename T, template<typename> class ... Constraints>
    ConfigValue<T, Constraints...> MakeValue(const std::string& name, Constraints<T>&&... constraints);

    template<typename T, template<typename> class ... Constraints>
    class ConfigValue : public Config {
        using ValueChecker = CombinedConstraint<T, Constraints...>;

    public:
        ConfigValue() = default;

        ConfigValue(const std::string& name)
                : Config(name) {}

        operator T() {
            return t_;
        }

        const T& Get() {
            return t_;
        }

        template <template<typename> class Constraint>
        Constraint<T> & GetConstraint() {
            return checker_.template Get<Constraint>();
        }

        TransformResult Parse(const rapidjson::Value& document) override {
            if (document.Is<T>() == false) {
                rapidjson::StringBuffer buffer;
                rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
                document.Accept(writer);
                return std::optional<internal::FailureCollection>(
                        Failure(fmt::format("Expected type: {}. Actual value was: {}",
                                TypeName<T>::name, buffer.GetString())));
            }

            t_ = document.Get<T>();

            return TransformResult();
        }

        TransformResult Validate() const override {
            return checker_.Check(t_);
        }

    private:
        ConfigValue(const std::string& name, ValueChecker&& checker)
        : checker_(std::forward<ValueChecker>(checker)) {}

        T t_;
        ValueChecker checker_;

        friend ConfigValue MakeValue<T, Constraints...>(const std::string& name, Constraints<T>&&... constraints);
    };

    template<typename T, template<typename> class ... Constraints>
    ConfigValue<T, Constraints...> MakeValue(const std::string& name, Constraints<T>&&... constraints) {
        return ConfigValue(name, MakeConstraint(std::forward<Constraints<T>>(constraints)...));
    }

}  // rapidjson

#endif //RAPIDJSON_CONFIGVALUE_H
