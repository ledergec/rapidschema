//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef INCLUDE_RAPIDSCHEMA_CONFIG_H_
#define INCLUDE_RAPIDSCHEMA_CONFIG_H_

#include <optional>
#include <string>

#include <rapidjson/document.h>

#include "rapidschema/abstract_writer.h"
#include "rapidschema/transform_result.h"

namespace rapidschema {

template <typename Ch = char>
class GenericConfig {
 public:
  virtual ~GenericConfig() = default;

  virtual TransformResult Parse(const rapidjson::Value &document) = 0;

  virtual TransformResult Validate() const = 0;

  virtual TransformResult HandleMissing() const = 0;

  virtual void Serialize(AbstractWriter<Ch>* writer) const = 0;
};

using Config = GenericConfig<>;

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_CONFIG_H_
