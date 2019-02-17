// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_CONSTANT_H_
#define INCLUDE_RAPIDSCHEMA_CONSTANT_H_

#include "rapidschema/value.h"
#include "rapidschema/result.h"

namespace rapidschema {

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION
template <typename T, class Enabled = void>
struct ConstantSchemaCreator;

template <typename T>
struct ConstantSchemaCreator<T, typename std::enable_if<TypeProperties<T>::GetJsonType() == JsonType::STRING>::type> {
  static std::shared_ptr<schema::SubSchema> CreateConstantSchema(
      const schema::SchemaAssemblerInterface & assembler,
      const T& t) {
    auto schema = assembler.CreateConstantStringSchema();
    schema->SetConstant(t);
    return schema->CreateSubSchema();
  }
};

template <typename T>
struct ConstantSchemaCreator<T, typename std::enable_if<std::is_integral<T>::value>::type> {
  static std::shared_ptr<schema::SubSchema> CreateConstantSchema(
      const schema::SchemaAssemblerInterface & assembler,
      const T& t) {
    auto schema = assembler.CreateConstantIntegerSchema();
    schema->SetConstant(t);
    return schema->CreateSubSchema();
  }
};

template <typename T>
struct ConstantSchemaCreator<T, typename std::enable_if<std::is_floating_point<T>::value>::type> {
  static std::shared_ptr<schema::SubSchema> CreateConstantSchema(
      const schema::SchemaAssemblerInterface & assembler,
      const T& t) {
    auto schema = assembler.CreateConstantNumberSchema();
    schema->SetConstant(t);
    return schema->CreateSubSchema();
  }
};
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
  virtual std::shared_ptr<schema::SubSchema> CreateSchema(const schema::SchemaAssemblerInterface & assembler) const {
    return ConstantSchemaCreator<T>::CreateConstantSchema(assembler, expected_value_);
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
