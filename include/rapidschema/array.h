// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_ARRAY_H_
#define INCLUDE_RAPIDSCHEMA_ARRAY_H_

#include <vector>

#include <fmt/format.h>

#include "rapidschema/config.h"
#include "rapidschema/rapidjson_type_to_string.h"
#include "rapidschema/result.h"

namespace rapidschema {

template<typename ConfigType, typename Ch = char>
class Array : public GenericConfig<Ch> {
 public:
  using CharType = Ch;

  Result Transform(const rapidjson::Value& document) override {
    if (document.IsArray() == false) {
      return Result(Failure(fmt::format("Expected array but was: {} ",
                                        JsonTypeToString(document.GetType()))));
    }

    Result result;
    size_t count = 0;
    auto dom_array = document.GetArray();
    for (const auto& dom_element : dom_array) {
      elements.emplace_back();
      auto tmp = elements.back().Transform(dom_element);
      if (tmp.HasFailures()) {
        tmp.PrependTokenToPointer(fmt::format("{}", count));
        result.Append(tmp);
      }
      count++;
    }

    return result;
  }

  Result Validate() const override {
    Result result;
    for (auto& e : elements) {
      result.Append(e.Validate());
    }

    return result;
  }

  void Serialize(AbstractWriter<Ch>* writer) const override {
    writer->StartArray();
    for (const auto& e : elements) {
      e.Serialize(writer);
    }
    writer->EndArray();
  }

  bool IsRequired() const override {
    return true;
  }

  void CollectMemory() const override {
    for (const auto& element : elements) {
      element.CollectMemory();
    }
  }

  void reserve(size_t size) {
    elements.reserve(size);
  }

  void push_back(const ConfigType& config) {
    elements.push_back(config);
  }

  ConfigType& operator[] (size_t i) {
    return elements[i];
  }

  const ConfigType& operator[] (size_t i) const {
    return elements[i];
  }

  typename std::vector<ConfigType>::iterator begin() {
    return elements.begin();
  }

  typename std::vector<ConfigType>::const_iterator begin() const {
    return elements.begin();
  }

  typename std::vector<ConfigType>::iterator end() {
    return elements.end();
  }

  typename std::vector<ConfigType>::const_iterator end() const {
    return elements.end();
  }

 private:
  std::vector<ConfigType> elements;
};

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_ARRAY_H_
