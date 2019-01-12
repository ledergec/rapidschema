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
  virtual ~GenericConfig() = default;

  virtual TransformResult Transform(const rapidjson::Value& document) = 0;

  virtual TransformResult Validate() const = 0;

  virtual TransformResult HandleMissing() const = 0;

  virtual void Serialize(AbstractWriter<Ch>* writer) const = 0;

  virtual void CollectMemory() const {}

#ifdef RAPIDSCHEMA_ENABLE_CROSS_VALIDATION
  virtual void SetCrossValidationResults(TransformResult&& cross_validation_results) {
    cross_validation_results_ = cross_validation_results;
  }

  virtual TransformResult CollectCrossValidationResults() const = 0;

 protected:
  TransformResult cross_validation_results_;
#endif
};

using Config = GenericConfig<>;

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_CONFIG_H_
