// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_CONFIG_H_
#define INCLUDE_RAPIDSCHEMA_CONFIG_H_

#include <rapidjson/document.h>

#include "rapidschema/abstract_writer.h"
#include "rapidschema/transform_result.h"

namespace rapidschema {

template <typename Ch = char>
class GenericConfig {
 public:
  using CharType = Ch;

  virtual ~GenericConfig() = default;

  virtual Result Transform(const rapidjson::Value& document) = 0;

  virtual Result Validate() const = 0;

  virtual Result HandleMissing() const = 0;

  virtual void Serialize(AbstractWriter<Ch>* writer) const = 0;

  virtual void CollectMemory() const {}
};

using Config = GenericConfig<>;

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_CONFIG_H_
