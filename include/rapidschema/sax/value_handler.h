//
// Created by root on 12/31/18.
//

#ifndef INCLUDE_RAPIDSCHEMA_SAX_VALUE_HANDLER_H_
#define INCLUDE_RAPIDSCHEMA_SAX_VALUE_HANDLER_H_

namespace rapidschema {

template<typename Type, typename Ch = char>
class ValueHandler : public AbstractHandler<Ch> {
 public:
  explicit ValueHandler(Type *t) {
    (void) t;
  }

  bool Null() override {
    assert(false);
    return true;
  }

  bool Bool(bool b) override {
    assert(false);
    return true;
  }

  bool Int(int i) override {
    assert(false);
    return true;
  }

  bool Uint(unsigned i) override {
    assert(false);
    return true;
  }

  bool Int64(int64_t i) override {
    assert(false);
    return true;
  }

  bool Uint64(uint64_t i) override {
    assert(false);
    return true;
  }

  bool Double(double d) override {
    assert(false);
    return true;
  }

  bool RawNumber(const Ch *str, rapidjson::SizeType length, bool copy) override {
    assert(false);
    return true;
  }

  bool String(const Ch *str, rapidjson::SizeType length, bool copy) override {
    assert(false);
    return true;
  }

  bool StartObject() override {
    assert(false);
    return true;
  }

  bool Key(const Ch *str, rapidjson::SizeType length, bool copy) override {
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
    assert(false);
    return true;
  }

  const TransformResult &GetResult() {
    assert(false);
    return result_;
  }

 private:
  TransformResult result_;
};

template<typename Ch>
class ValueHandler<int32_t, Ch> : public AbstractHandler<Ch> {
 public:
  explicit ValueHandler(int32_t *t)
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

  bool RawNumber(const Ch *str, rapidjson::SizeType length, bool copy) override {
    assert(false);
    return true;
  }

  bool String(const Ch *str, rapidjson::SizeType length, bool copy) override {
    finished_ = true;
    result_ = FailResult("Expected int32 but was string");
    return true;
  }

  bool StartObject() override {
    assert(false);
    return true;
  }

  bool Key(const Ch *str, rapidjson::SizeType length, bool copy) override {
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

  const TransformResult &GetResult() {
    return result_;
  }

 private:
  int32_t *t_;
  TransformResult result_;
  bool finished_;
};

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_SAX_VALUE_HANDLER_H_
