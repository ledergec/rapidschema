//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef INCLUDE_RAPIDSCHEMA_CONFIGVALUE_H_
#define INCLUDE_RAPIDSCHEMA_CONFIGVALUE_H_

#include <optional>
#include <string>

#include <fmt/format.h>

#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

#include "rapidschema/combined_constraint.h"
#include "rapidschema/concepts/requires_macro.h"
#include "rapidschema/concepts/correct_value_parameters.h"
#include "rapidschema/config.h"
#include "rapidschema/transform_result.h"
#include "rapidschema/type_properties.h"

namespace rapidschema {

template <typename Type, typename Ch = char>
class ValueHandler : public AbstractHandler<Ch> {
 public:
  ValueHandler(int32_t * t) {}

  bool Null() override {
    finished_ = true;
    result_ = FailResult("Expected int32 but was null");
    return true;
  }

  bool Bool(bool b) override {
    finished_ = true;
    result_ = FailResult("Expected int32 but was bool");
    return true;
  }

  bool Int(int i) override {
    *t_ = i;
    return true;
  }

  bool Uint(unsigned i) override {
    if (i < std::numeric_limits<int32_t>::max()) {
      *t_ = static_cast<int32_t>(i);
      return true;
    } else {
      finished_ = true;
      result_ = FailResult("Expected int32 but was uint32");
      return true;
    }
  }

  bool Int64(int64_t i) override {
    if (std::numeric_limits<int32_t>::min() < i && i < std::numeric_limits<int32_t>::max()) {
      *t_ = static_cast<int32_t>(i);
      return true;
    } else {
      finished_ = true;
      result_ = FailResult("Expected int32 but was int64");
      return true;
    }
  }

  bool Uint64(uint64_t i) override {
    if (i < std::numeric_limits<int32_t>::max()) {
      *t_ = static_cast<int32_t>(i);
      return true;
    } else {
      finished_ = true;
      result_ = FailResult("Expected int32 but was uint64");
      return true;
    }
  }

  bool Double(double d) override {
    finished_ = true;
    result_ = FailResult("Expected int32 but was double");
    return true;
  }

  bool RawNumber(const Ch* str, rapidjson::SizeType length, bool copy) override {
    assert(false);
    return true;
  }

  bool String(const Ch* str, rapidjson::SizeType length, bool copy) override {
    finished_ = true;
    result_ = FailResult("Expected int32 but was string");
    return true;
  }

  bool StartObject() override {
    assert(false);
    finished_ = true;
    result_ = FailResult("Expected int32 but was object");
    return true;
  }

  bool Key(const Ch* str, rapidjson::SizeType length, bool copy) override {
    assert(false);
    return true;
  }

  bool EndObject(rapidjson::SizeType memberCount) override {
    assert(false);
    return true;
  }

  bool StartArray() override {
    assert(false);
    return true;
  }

  bool EndArray(rapidjson::SizeType elementCount) override {
    assert(false);
    return true;
  }

  bool IsFinished() {
    return finished_;
  }

  const TransformResult & GetResult() {
    return result_;
  }

 private:
  int32_t * t_;
  TransformResult result_;
  bool finished_;
};

template <typename Ch>
class ValueHandler<int32_t, Ch> : public AbstractHandler<Ch> {
 public:
  ValueHandler(int32_t * t)
      : t_(t) {}

  bool Null() override {
    finished_ = true;
    result_ = FailResult("Expected int32 but was null");
    return true;
  }

  bool Bool(bool b) override {
    finished_ = true;
    result_ = FailResult("Expected int32 but was bool");
    return true;
  }

  bool Int(int i) override {
    *t_ = i;
    return true;
  }

  bool Uint(unsigned i) override {
    if (i < std::numeric_limits<int32_t>::max()) {
      *t_ = static_cast<int32_t>(i);
      return true;
    } else {
      finished_ = true;
      result_ = FailResult("Expected int32 but was uint32");
      return true;
    }
  }

  bool Int64(int64_t i) override {
    if (std::numeric_limits<int32_t>::min() < i && i < std::numeric_limits<int32_t>::max()) {
      *t_ = static_cast<int32_t>(i);
      return true;
    } else {
      finished_ = true;
      result_ = FailResult("Expected int32 but was int64");
      return true;
    }
  }

  bool Uint64(uint64_t i) override {
    if (i < std::numeric_limits<int32_t>::max()) {
      *t_ = static_cast<int32_t>(i);
      return true;
    } else {
      finished_ = true;
      result_ = FailResult("Expected int32 but was uint64");
      return true;
    }
  }

  bool Double(double d) override {
    finished_ = true;
    result_ = FailResult("Expected int32 but was double");
    return true;
  }

  bool RawNumber(const Ch* str, rapidjson::SizeType length, bool copy) override {
    assert(false);
    return true;
  }

  bool String(const Ch* str, rapidjson::SizeType length, bool copy) override {
    finished_ = true;
    result_ = FailResult("Expected int32 but was string");
    return true;
  }

  bool StartObject() override {
    assert(false);
    finished_ = true;
    result_ = FailResult("Expected int32 but was object");
    return true;
  }

  bool Key(const Ch* str, rapidjson::SizeType length, bool copy) override {
    assert(false);
    return true;
  }

  bool EndObject(rapidjson::SizeType memberCount) override {
    assert(false);
    return true;
  }

  bool StartArray() override {
    assert(false);
    return true;
  }

  bool EndArray(rapidjson::SizeType elementCount) override {
    assert(false);
    return true;
  }

  bool IsFinished() {
    return finished_;
  }

  const TransformResult & GetResult() {
    return result_;
  }

 private:
  int32_t * t_;
  TransformResult result_;
  bool finished_;
};


template <typename Ch>
class ValueHandler<int64_t, Ch> : public AbstractHandler<Ch> {
 public:
  ValueHandler(int64_t * t)
      : t_(t) {}

  bool Null() override {
    return true;
  }

  bool Bool(bool b) override {
    return true;
  }

  bool Int(int i) override {
    *t_ = i;
    return true;
  }

  bool Uint(unsigned i) override {
    *t_ = i;
    return true;
  }

  bool Int64(int64_t i) override {
    *t_ = i;
    return true;
  }

  bool Uint64(uint64_t i) override {
    if (i < std::numeric_limits<int64_t>::max()) {
      *t_ = static_cast<int64_t>(i);
      return true;
    } else {
      return true;
    }
  }

  bool Double(double d) override {
    return true;
  }

  bool RawNumber(const Ch* str, rapidjson::SizeType length, bool copy) override {
    assert(false);
    return true;
  }

  bool String(const Ch* str, rapidjson::SizeType length, bool copy) override {
    return true;
  }

  bool StartObject() override {
    return true;
  }

  bool Key(const Ch* str, rapidjson::SizeType length, bool copy) override {
    return true;
  }

  bool EndObject(rapidjson::SizeType memberCount) override {
    return true;
  }

  bool StartArray() override {
    return true;
  }

  bool EndArray(rapidjson::SizeType elementCount) override {
    return true;
  }

 private:
  int64_t * t_;
};

template <typename Ch>
class ValueHandler<std::string, Ch> : public AbstractHandler<Ch> {
 public:
  ValueHandler(std::string * t)
      : t_(t) {}

  bool Null() override {
    return true;
  }

  bool Bool(bool b) override {
    return true;
  }

  bool Int(int i) override {
    return true;
  }

  bool Uint(unsigned i) override {
    return true;
  }

  bool Int64(int64_t i) override {
    return true;
  }

  bool Uint64(uint64_t i) override {
    return true;
  }

  bool Double(double d) override {
    return true;
  }

  bool RawNumber(const Ch* str, rapidjson::SizeType length, bool copy) override {
    assert(false);
    return true;
  }

  bool String(const Ch* str, rapidjson::SizeType length, bool copy) override {
    t_->clear();
    t_->append(str, length);
    return true;
  }

  bool StartObject() override {
    return true;
  }

  bool Key(const Ch* str, rapidjson::SizeType length, bool copy) override {
    return true;
  }

  bool EndObject(rapidjson::SizeType memberCount) override {
    return true;
  }

  bool StartArray() override {
    return true;
  }

  bool EndArray(rapidjson::SizeType elementCount) override {
    return true;
  }

 private:
  std::string * t_;
};


template<typename Ch, typename T, template<typename> class ... Constraints>
    RAPIDSCHEMA_REQUIRES((CorrectValueParameters<T, Constraints...>))
class GenericValue;

template<typename T, template<typename> class ... Constraints>
    RAPIDSCHEMA_REQUIRES((CorrectValueParameters<T, Constraints...>))
GenericValue<char, T, Constraints...>
    MakeUtf8Value(Constraints<T>&&... constraints);

template<typename Ch, typename T, template<typename> class ... Constraints>
    RAPIDSCHEMA_REQUIRES((CorrectValueParameters<T, Constraints...>))
class GenericValue : public GenericConfig<Ch> {
 private:
  using ValueChecker = CombinedConstraint<T, Constraints...>;

 public:
  GenericValue() = default;

  using Type = T;

  GenericValue<Ch, T, Constraints...>& operator=(const T& t) {
    t_ = t;
    return *this;
  }

  operator T() {
    return t_;
  }

  const T& Get() const {
    return t_;
  }

  template <template<typename> class Constraint>
  Constraint<T> & GetConstraint() {
    return checker_.template Get<Constraint>();
  }

  TransformResult Parse(AbstractReader<Ch> * reader) override {
    ValueHandler<T, Ch> handler(&t_);
    while (handler.IsFinished() == false && reader->HasParseError() == false) {
      reader->Next(&handler);
    }
    if (reader->HasParseError()) {
      // TODO(cledergerber) convert rapidjson message to string
      return TransformResult(Failure(fmt::format("Encountered errors while parsing.")));
    }
    return handler.GetResult();
  }

  TransformResult Parse(const rapidjson::Value& document) override {
    if (TypeProperties<T>::IsType(document) == false) {
      rapidjson::StringBuffer buffer;
      rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
      document.Accept(writer);
      return FailResult(
          fmt::format("Expected type: {}. Actual value was: {}", TypeProperties<T>::name, buffer.GetString()));
    }

    t_ = TypeProperties<T>::FromJson(document);

    return TransformResult();
  }

  TransformResult Validate() const override {
    return checker_.Check(t_);
  }

  void Serialize(AbstractWriter<Ch>* writer) const override {
    TypeProperties<T>::Serialize(t_, writer);
  }

  TransformResult HandleMissing() const override {
    return FailResult("is missing");
  }

 private:
  GenericValue(ValueChecker&& checker)
      : checker_(std::forward<ValueChecker>(checker)) {}

  T t_;
  ValueChecker checker_;

  friend GenericValue MakeUtf8Value<T, Constraints...>(Constraints<T>&&... constraints);
};

template <typename T, template<typename> class ... Constraints>
using Value = GenericValue<char, T, Constraints...>;

template<typename T, template<typename> class ... Constraints>
    RAPIDSCHEMA_REQUIRES((CorrectValueParameters<T, Constraints...>))
GenericValue<char, T, Constraints...>
    MakeUtf8Value(Constraints<T>&&... constraints) {
  return GenericValue<char, T, Constraints...>(MakeConstraint<T, Constraints...>(std::forward<Constraints<T>>(constraints)...));
}

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_CONFIGVALUE_H_
