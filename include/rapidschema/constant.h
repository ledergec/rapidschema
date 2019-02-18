// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_CONSTANT_H_
#define INCLUDE_RAPIDSCHEMA_CONSTANT_H_

#include "rapidschema/value.h"
#include "rapidschema/result.h"

namespace rapidschema {

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION
namespace internal {
template<typename T, class Enabled = void>
struct ConstantSchemaCreator;

template<typename T>
struct ConstantSchemaCreator<T, typename std::enable_if<TypeProperties<T>::GetJsonType() == JsonType::BOOLEAN>::type> {
  static std::shared_ptr<schema::ConstantBooleanSchemaInterface> CreateConstantSchema(
      const schema::SchemaAssemblerInterface& assembler) {
    return assembler.CreateConstantBooleanSchema();
  }
};

template<typename T>
struct ConstantSchemaCreator<T, typename std::enable_if<TypeProperties<T>::GetJsonType() == JsonType::INTEGER>::type> {
  static std::shared_ptr<schema::ConstantIntegerSchemaInterface> CreateConstantSchema(
      const schema::SchemaAssemblerInterface& assembler) {
    return assembler.CreateConstantIntegerSchema();
  }
};

template<typename T>
struct ConstantSchemaCreator<T, typename std::enable_if<TypeProperties<T>::GetJsonType() == JsonType::NUMBER>::type> {
  static std::shared_ptr<schema::ConstantNumberSchemaInterface> CreateConstantSchema(
      const schema::SchemaAssemblerInterface& assembler) {
    return assembler.CreateConstantNumberSchema();
  }
};

template<typename T>
struct ConstantSchemaCreator<T, typename std::enable_if<TypeProperties<T>::GetJsonType() == JsonType::STRING>::type> {
  static std::shared_ptr<schema::ConstantStringSchemaInterface> CreateConstantSchema(
      const schema::SchemaAssemblerInterface& assembler) {
    return assembler.CreateConstantStringSchema();
  }
};
}  // namespace internal
#endif

template<typename Ch, typename T>
class GenericConstant : public GenericValue<Ch, T> {
 public:
  using GenericValue<Ch, T>::operator=;

  void SetExpectedValue(const T& expected_value) {
    expected_value_ = expected_value;
  }

  const T& GetExpectedValue() const {
    return this->t_;
  }

  Result Transform(const rapidjson::Value& document) override {
    auto result = GenericValue<Ch, T>::Transform(document);
    if (result.Success()) {
      return ValidateInternal();
    } else {
      return result;
    }
  }

  Result Validate() const override {
    return ValidateInternal();
  }

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION
  std::shared_ptr<schema::SubSchema> CreateSchema(const schema::SchemaAssemblerInterface & assembler) const override {
    auto result = internal::ConstantSchemaCreator<T>::CreateConstantSchema(assembler);
    result->SetConstant(expected_value_);
    return result->CreateSubSchema();
  }
#endif

 private:
  Result ValidateInternal() const {
    if (this->t_ == expected_value_) {
      return Result();
    } else {
      return FailResult(fmt::format("Expected constant value: {}, actual: {}.", expected_value_, this->t_));
    }
  }

  T expected_value_;
};

template <typename T>
using Constant = GenericConstant<char, T>;

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_CONSTANT_H_
