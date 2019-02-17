// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_UTILS_REGEX_H_
#define INCLUDE_RAPIDSCHEMA_UTILS_REGEX_H_

#include <regex>

namespace rapidschema {

/// This class provides basic regex support for JSONSchemas. JSONSchema regex follows the ECMA-262 regex specification
/// http://www.ecma-international.org/publications/standards/Ecma-262.htm. The current implementation relies on the
/// regex implementation in the stl which is not an exact implemenation of the standard, but a modified version. See
/// https://en.cppreference.com/w/cpp/regex/ecmascript for reference.
template<typename CharType = char>
class Regex {
 public:
  using RegexType = std::basic_regex<CharType>;
  using StringType = std::basic_string<CharType>;

  static RegexType CreateRegex(const StringType& pattern) {
    try {
      return RegexType(pattern);
    } catch (std::regex_error& error) {
      assert(false);
    }
  }

  static bool IsCompleteMatch(const RegexType& regex, const StringType& string) {
    return std::regex_match(string, regex);
  }
};

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_UTILS_REGEX_H_