// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_ARRAY_H_
#define INCLUDE_RAPIDSCHEMA_ARRAY_H_

#include <vector>

#include <fmt/format.h>

#include "rapidschema/config.h"
#include "rapidschema/rapidjson_type_to_string.h"
#include "rapidschema/transform_result.h"

namespace rapidschema {

template<typename T, typename Ch = char>
class Array : public GenericConfig<Ch> {
 public:
  using CharType = Ch;

  TransformResult Parse(const rapidjson::Value & document) override {
    if (document.IsArray() == false) {
      return TransformResult(Failure(fmt::format("Expected array but was: {} ",
                                                 JsonTypeToString(document.GetType()))));
    }

    TransformResult result;
    size_t count = 0;
    auto dom_array = document.GetArray();
    for (const auto & dom_element : dom_array) {
      elements.emplace_back();
      auto tmp = elements.back().Parse(dom_element);
      if (tmp.HasFailures()) {
        tmp.AddPath(fmt::format("[{}]", count));
        result.Append(tmp);
      }
      count++;
    }

    return result;
  }

  TransformResult Validate() const override {
    TransformResult result;
    for (auto & e : elements) {
      result.Append(e.Validate());
    }

    return result;
  }

  void Serialize(AbstractWriter<Ch>* writer) const override {
    writer->StartArray();
    for (const auto & e : elements) {
      e.Serialize(writer);
    }
    writer->EndArray();
  }

  TransformResult HandleMissing() const override {
    return TransformResult(Failure("Array is missing"));
  }

  void CollectMemory() const override {
    for (const auto & element : elements) {
      element.CollectMemory();
    }
  }

  void reserve(size_t size) {
    elements.reserve(size);
  }

  void push_back(const T& t) {
    elements.push_back(t);
  }

  T& operator[] (size_t i) {
    return elements[i];
  }

  const T& operator[] (size_t i) const {
    return elements[i];
  }

  auto begin() {
    return elements.begin();
  }

  const auto begin() const {
    return elements.begin();
  }

  auto end() {
    return elements.end();
  }

  const auto end() const {
    return elements.end();
  }

 private:
  std::vector<T> elements;
};

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_ARRAY_H_
