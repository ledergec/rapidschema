// Copyright (C) 2019 Christian Ledergerber

#ifndef UNITTESTS_RAPIDSCHEMA_TO_JSON_LITERAL_H_
#define UNITTESTS_RAPIDSCHEMA_TO_JSON_LITERAL_H_

#include <string>

#include <fmt/format.h>

template<typename ConfigType, class Enable = void>
struct ToJsonLiteral;

template <>
struct ToJsonLiteral<const char*> {
  static std::string Convert(const char* str) {
    return fmt::format(R"("{}")", str);
  }
};

template <size_t N>
struct ToJsonLiteral<char[N]> {
  static std::string Convert(const char* str) {
    return fmt::format(R"("{}")", str);
  }
};

template <>
struct ToJsonLiteral<std::string> {
  static std::string Convert(const std::string& c) {
    return fmt::format(R"("{}")", c);
  }
};

template <>
struct ToJsonLiteral<std::nullptr_t, std::enable_if<std::true_type::value>::type> {
  static std::string Convert(const std::nullptr_t& c) {
    return "null";
  }
};

template <typename ConfigType>
struct ToJsonLiteral<ConfigType, typename std::enable_if<std::is_integral<ConfigType>::value>::type> {
  static std::string Convert(const ConfigType& c) {
    return fmt::format(R"({})", c);
  }
};

template <typename ConfigType>
struct ToJsonLiteral<ConfigType, typename std::enable_if<std::is_floating_point<ConfigType>::value>::type> {
  static std::string Convert(const ConfigType& c) {
    return fmt::format(R"({:.1f})", c);
  }
};

#endif  // UNITTESTS_RAPIDSCHEMA_TO_JSON_LITERAL_H_
