// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_TYPE_PROPERTIES_H_
#define INCLUDE_RAPIDSCHEMA_TYPE_PROPERTIES_H_

#include <string>
#include <type_traits>

#include <rapidjson/document.h>

#include "rapidschema/abstract_writer.h"

namespace rapidschema {

// json types as specified by the json schema draft v6
enum struct JsonType {
  OBJECT,
  ARRAY,
  STRING,
  INTEGER,
  NUMBER,
  BOOLEAN,
  NULLTYPE
};

template<typename T>
struct TypeProperties;

template<typename Ch>
struct TypeProperties<std::basic_string<Ch>> {
  static constexpr JsonType GetJsonType() {
    return JsonType::STRING;
  }

  static std::string GetName() {
    return "string";
  }

  static bool IsType(const rapidjson::Value& value) {
      return value.IsString();
  }

  static std::string FromJson(const rapidjson::Value& value) {
      return value.GetString();
  }

  template <typename TargetCh>
  static void Serialize(const std::basic_string<Ch>& str, AbstractWriter<TargetCh>* writer) {
    writer->String(str.c_str());
  }
};

template<>
struct TypeProperties<int32_t> {
  static constexpr JsonType GetJsonType() {
    return JsonType::INTEGER;
  }

  static std::string GetName() {
    return "int";
  }

  static bool IsType(const rapidjson::Value& value) {
      return value.IsInt();
  }

  static int32_t FromJson(const rapidjson::Value& value) {
      return value.GetInt();
  }

  template <typename TargetCh>
  static void Serialize(const int32_t& i, AbstractWriter<TargetCh>* writer) {
    writer->Int(i);
  }
};

template<>
struct TypeProperties<uint32_t> {
  static constexpr JsonType GetJsonType() {
    return JsonType::INTEGER;
  }

  static std::string GetName() {
    return "unsigned int";
  }

  static bool IsType(const rapidjson::Value& value) {
      return value.IsUint();
  }

  static uint32_t FromJson(const rapidjson::Value& value) {
      return value.GetUint();
  }

  template <typename TargetCh>
  static void Serialize(const uint32_t& i, AbstractWriter<TargetCh>* writer) {
    writer->Uint(i);
  }
};

template<>
struct TypeProperties<int64_t> {
  static constexpr JsonType GetJsonType() {
    return JsonType::INTEGER;
  }

  static std::string GetName() {
    return "long int";
  }

  static bool IsType(const rapidjson::Value& value) {
      return value.IsInt64();
  }

  static int64_t FromJson(const rapidjson::Value& value) {
      return value.GetInt64();
  }

  template <typename TargetCh>
  static void Serialize(const int64_t& i, AbstractWriter<TargetCh>* writer) {
    writer->Int64(i);
  }
};


template<>
struct TypeProperties<uint64_t> {
  static constexpr JsonType GetJsonType() {
    return JsonType::INTEGER;
  }

  static std::string GetName() {
    return "unsigned long int";
  }

  static bool IsType(const rapidjson::Value& value) {
      return value.IsUint64();
  }

  static int64_t FromJson(const rapidjson::Value& value) {
      return value.GetUint64();
  }

  template <typename TargetCh>
  static void Serialize(const uint64_t& i, AbstractWriter<TargetCh>* writer) {
    writer->Uint64(i);
  }
};

template<>
struct TypeProperties<bool> {
  static constexpr JsonType GetJsonType() {
    return JsonType::BOOLEAN;
  }

  static std::string GetName() {
    return "boolean";
  }

  static bool IsType(const rapidjson::Value& value) {
      return value.IsBool();
  }

  static bool FromJson(const rapidjson::Value& value) {
      return value.GetBool();
  }

  template <typename TargetCh>
  static void Serialize(const bool& b, AbstractWriter<TargetCh>* writer) {
    writer->Bool(b);
  }
};


template<>
struct TypeProperties<float> {
  static constexpr JsonType GetJsonType() {
    return JsonType::NUMBER;
  }

  static std::string GetName() {
    return "float";
  }

  static bool IsType(const rapidjson::Value& value) {
      return value.IsFloat();
  }

  static float FromJson(const rapidjson::Value& value) {
      return value.GetFloat();
  }

  template <typename TargetCh>
  static void Serialize(const float& f, AbstractWriter<TargetCh>* writer) {
    writer->Double(f);
  }
};

template<>
struct TypeProperties<double> {
  static constexpr JsonType GetJsonType() {
    return JsonType::NUMBER;
  }

  static std::string GetName() {
    return "double";
  }

  static bool IsType(const rapidjson::Value& value) {
      return value.IsDouble();
  }

  static double FromJson(const rapidjson::Value& value) {
      return value.GetDouble();
  }

  template <typename TargetCh>
  static void Serialize(const double& d, AbstractWriter<TargetCh>* writer) {
    writer->Double(d);
  }
};

template<>
struct TypeProperties<std::nullptr_t> {
  static constexpr JsonType GetJsonType() {
    return JsonType::NULLTYPE;
  }

  static std::string GetName() {
    return "nullptr";
  }

  static bool IsType(const rapidjson::Value& value) {
      return value.IsNull();
  }

  static std::nullptr_t FromJson(const rapidjson::Value& value) {
      return nullptr;
  }

  template <typename TargetCh>
  static void Serialize(const std::nullptr_t& n, AbstractWriter<TargetCh>* writer) {
    (void) n;
    writer->Null();
  }
};

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_TYPE_PROPERTIES_H_
