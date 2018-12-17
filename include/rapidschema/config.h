//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef INCLUDE_RAPIDSCHEMA_CONFIG_H_
#define INCLUDE_RAPIDSCHEMA_CONFIG_H_

#include <optional>
#include <string>

#include <rapidjson/document.h>

#include "rapidschema/transform_result.h"
#include "rapidschema/abstract_writer.h"

namespace rapidschema {

template <typename Encoding = rapidjson::UTF8<>>
class GenericConfig {
 protected:
  using Ch = typename Encoding::Ch;

 public:
  GenericConfig()
      : name_("") {}

  explicit GenericConfig(const std::basic_string<Ch> &name)
      : name_(name) {}

  virtual ~GenericConfig() = default;

  virtual TransformResult Parse(const rapidjson::Value &document) = 0;

  virtual TransformResult Validate() const = 0;

  virtual void Serialize(AbstractWriter<Encoding>* writer) const = 0;

  const std::string& GetName() const {
    return name_;
  }

  void SetName(const std::basic_string<Ch> &name) {
    name_ = name;
  }

 private:
  std::basic_string<Ch> name_;
};

using Config = GenericConfig<>;

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_CONFIG_H_
