// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_PATTERN_PROPERTY_INTERFACE_H_
#define INCLUDE_RAPIDSCHEMA_PATTERN_PROPERTY_INTERFACE_H_

#include <assert.h>

#include <string>
#include <unordered_map>

#include <rapidjson/document.h>

#include "rapidschema/result.h"
#include "rapidschema/utils/regex.h"

namespace rapidschema {

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION
namespace schema {
class SchemaAssemblerInterface;
}  // namespace schema
#endif

template <typename Ch = char>
class PatternPropertyInterface {
 public:
  using CharType = Ch;
  using StringType = std::basic_string<CharType>;

  virtual const StringType & GetPattern() const = 0;

  virtual bool IsMatchingName(const StringType & name) const = 0;

  virtual Result Transform(const StringType & name, const rapidjson::Value& document) = 0;

  virtual Result Validate() const = 0;

  virtual void Serialize(AbstractWriter<CharType>* writer) const = 0;

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION
  virtual std::shared_ptr<schema::SubSchema> CreateSchema(const schema::SchemaAssemblerInterface & assembler) const = 0;
#endif
};

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_PATTERN_PROPERTY_INTERFACE_H_
