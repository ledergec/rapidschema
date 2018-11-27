//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef RAPIDJSON_TO_JSON_TYPE_H
#define RAPIDJSON_TO_JSON_TYPE_H

#include <string>
#include <type_traits>

#include <rapidjson/document.h>

namespace rapidoson {

    // json types as specified by the json schema draft v6
    enum struct JsonType {
        OBJECT,
        ARRAY,
        STRING,
        NUMBER,
        BOOLEAN,
        NULLTYPE
    };

    template<typename T>
    struct TypeProperties;

    template<>
    struct TypeProperties<std::string> {
        static constexpr JsonType json_type = JsonType::STRING;
        static constexpr char name[] = "std::string";

        static bool IsType(const rapidjson::Value &value) {
            return value.IsString();
        }

        static std::string FromJson(const rapidjson::Value &value) {
            return value.GetString();
        }
    };

    template<>
    struct TypeProperties<int32_t> {
        static constexpr JsonType json_type = JsonType::NUMBER;
        static constexpr char name[] = "int";

        static bool IsType(const rapidjson::Value &value) {
            return value.IsInt();
        }

        static int32_t FromJson(const rapidjson::Value &value) {
            return value.GetInt();
        }
    };

    template<>
    struct TypeProperties<uint32_t> {
        static constexpr JsonType json_type = JsonType::NUMBER;
        static constexpr char name[] = "unsigned int";

        static bool IsType(const rapidjson::Value &value) {
            return value.IsUint();
        }

        static uint32_t FromJson(const rapidjson::Value &value) {
            return value.GetUint();
        }
    };

    template<>
    struct TypeProperties<int64_t> {
        static constexpr JsonType json_type = JsonType::NUMBER;
        static constexpr char name[] = "long int";

        static bool IsType(const rapidjson::Value &value) {
            return value.IsInt64();
        }

        static int64_t FromJson(const rapidjson::Value &value) {
            return value.GetInt64();
        }
    };


    template<>
    struct TypeProperties<uint64_t> {
        static constexpr JsonType json_type = JsonType::NUMBER;
        static constexpr char name[] = "unsigned long int";

        static bool IsType(const rapidjson::Value &value) {
            return value.IsUint64();
        }

        static int64_t FromJson(const rapidjson::Value &value) {
            return value.GetUint64();
        }
    };

    template<>
    struct TypeProperties<bool> {
        static constexpr JsonType json_type = JsonType::BOOLEAN;
        static constexpr char name[] = "boolean";

        static bool IsType(const rapidjson::Value &value) {
            return value.IsBool();
        }

        static bool FromJson(const rapidjson::Value &value) {
            return value.GetBool();
        }
    };


    template<>
    struct TypeProperties<float> {
        static constexpr JsonType json_type = JsonType::NUMBER;
        static constexpr char name[] = "float";

        static bool IsType(const rapidjson::Value &value) {
            return value.IsFloat();
        }

        static float FromJson(const rapidjson::Value &value) {
            return value.GetFloat();
        }
    };

    template<>
    struct TypeProperties<double> {
        static constexpr JsonType json_type = JsonType::NUMBER;
        static constexpr char name[] = "double";

        static bool IsType(const rapidjson::Value &value) {
            return value.IsDouble();
        }

        static double FromJson(const rapidjson::Value &value) {
            return value.GetDouble();
        }
    };

    template<>
    struct TypeProperties<std::nullptr_t > {
        static constexpr JsonType json_type = JsonType::NULLTYPE;
        static constexpr char name[] = "nullptr_t";

        static bool IsType(const rapidjson::Value &value) {
            return value.IsNull();
        }

        static std::nullptr_t FromJson(const rapidjson::Value &value) {
            return nullptr;
        }
    };

}  // rapidjson

#endif //RAPIDJSON_TO_JSON_TYPE_H
