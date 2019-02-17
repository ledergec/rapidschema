// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_CONFIG_H_
#define INCLUDE_RAPIDSCHEMA_CONFIG_H_

#include <rapidjson/document.h>

#include "rapidschema/abstract_writer.h"
#include "rapidschema/result.h"

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION
#include "rapidschema/schema/schema_assembler_interface.h"
#endif

namespace rapidschema {

namespace schema {
class SubSchema;
}  // namespace schema

template <typename Ch = char>
class GenericConfig {
 public:
  using CharType = Ch;

  virtual ~GenericConfig() = default;

  virtual Result Transform(const rapidjson::Value& document) = 0;

  virtual Result Validate() const = 0;

  virtual bool IsRequired() const = 0;

  virtual void Serialize(AbstractWriter<Ch>* writer) const = 0;

  virtual void CollectMemory() const {}

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION
  virtual std::shared_ptr<schema::SubSchema> CreateSchema(const schema::SchemaAssemblerInterface & assembler) const {
    assert(false);
    return nullptr;
  }
#endif
};

using Config = GenericConfig<>;

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_CONFIG_H_
