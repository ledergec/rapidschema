//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef INCLUDE_RAPIDSCHEMA_TYPE_PROPERTIES_H_
#define INCLUDE_RAPIDSCHEMA_TYPE_PROPERTIES_H_

#include <string>
#include <type_traits>

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

namespace rapidschema {

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

  static void Serialize(const std::string& str, rapidjson::Writer<rapidjson::StringBuffer> * writer) {
    writer->String(str.c_str());
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

  static void Serialize(const int32_t& i, rapidjson::Writer<rapidjson::StringBuffer> * writer) {
    writer->Int(i);
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

  static void Serialize(const uint32_t& i, rapidjson::Writer<rapidjson::StringBuffer> * writer) {
    writer->Uint(i);
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

  static void Serialize(const int64_t& i, rapidjson::Writer<rapidjson::StringBuffer> * writer) {
    writer->Int64(i);
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

  static void Serialize(const uint64_t& i, rapidjson::Writer<rapidjson::StringBuffer> * writer) {
    writer->Uint64(i);
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

  static void Serialize(const bool& b, rapidjson::Writer<rapidjson::StringBuffer> * writer) {
    writer->Bool(b);
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

  static void Serialize(const float& f, rapidjson::Writer<rapidjson::StringBuffer> * writer) {
    writer->Double(f);
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

  static void Serialize(const double& d, rapidjson::Writer<rapidjson::StringBuffer> * writer) {
    writer->Double(d);
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

  static void Serialize(const nullptr_t& n, rapidjson::Writer<rapidjson::StringBuffer> * writer) {
    (void) n;
    writer->Null();
  }
};

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_TYPE_PROPERTIES_H_
