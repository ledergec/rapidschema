// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_PATTERN_PROPERTY_INTERFACE_H_
#define INCLUDE_PATTERN_PROPERTY_INTERFACE_H_

#include <assert.h>

#include <string>
#include <unordered_map>

#include <rapidjson/document.h>

#include "rapidschema/result.h"
#include "rapidschema/utils/regex.h"

namespace rapidschema {

template <typename Ch = char>
class PatternPropertyInterface {
 public:
  using CharType = Ch;
  using StringType = std::basic_string<CharType>;

  virtual bool IsMatchingName(const StringType & name) const = 0;

  virtual Result Transform(StringType & name, const rapidjson::Value& document) = 0;

  virtual Result Validate() const = 0;

  virtual void Serialize(AbstractWriter<CharType>* writer) const = 0;
};

}  // namespace rapidschema

#endif  // INCLUDE_PATTERN_PROPERTY_INTERFACE_H_
