//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef INCLUDE_RAPIDSCHEMA_CONFIG_H_
#define INCLUDE_RAPIDSCHEMA_CONFIG_H_

#include <optional>
#include <string>

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

#include "rapidschema/transform_result.h"

namespace rapidschema {

class Config {
 public:
  Config()
      : name_("") {}

  explicit Config(const std::string &name)
      : name_(name) {}

  virtual ~Config() = default;

  virtual TransformResult Parse(const rapidjson::Value &document) = 0;

  virtual TransformResult Validate() const = 0;

  virtual void Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const = 0;

  const std::string& GetName() const {
    return name_;
  }

  void SetName(const std::string &name) {
    name_ = name;
  }

 private:
  std::string name_;
};

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_CONFIG_H_
