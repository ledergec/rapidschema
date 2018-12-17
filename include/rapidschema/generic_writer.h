//
// Created by root on 12/12/18.
//

#ifndef INCLUDE_RAPIDSCHEMA_GENERIC_WRITER_H_
#define INCLUDE_RAPIDSCHEMA_GENERIC_WRITER_H_

#include "rapidschema/abstract_writer.h"

namespace rapidschema {

template<typename Writer, typename Encoding = rapidjson::UTF8<>>
class GenericWriter : public AbstractWriter<Encoding> {
  using Ch = typename AbstractWriter<Encoding>::Ch;
 public:
  template<typename ... Args>
  explicit GenericWriter(Args&&... args)
      : writer_(std::forward<Args>(args)...) {}

  bool IsComplete() const override {
    return writer_.IsComplete();
  }

  int GetMaxDecimalPlaces() const override {
    return writer_.GetMaxDecimalPlaces();
  }

  void SetMaxDecimalPlaces(int maxDecimalPlaces) override {
    writer_.SetMaxDecimalPlaces(maxDecimalPlaces);
  }

  bool Null() override {
    return writer_.Null();
  }

  bool Bool(bool b) override {
    return writer_.Bool(b);
  }

  bool Int(int i) override {
    return writer_.Int(i);
  }

  bool Uint(unsigned u) override {
    return writer_.Uint(u);
  }

  bool Int64(int64_t i64) override {
    return writer_.Int64(i64);
  }

  bool Uint64(uint64_t u64) override {
    return writer_.Uint64(u64);
  }

  bool Double(double d) override {
    return writer_.Double(d);
  }

  bool RawNumber(const Ch *str, rapidjson::SizeType length, bool copy = false) override {
    return writer_.RawNumber(str, length, copy);
  }

  bool String(const Ch *str, rapidjson::SizeType length, bool copy = false) override {
    return writer_.String(str, length, copy);
  }

  bool String(const std::basic_string<Ch> &str) override {
    return writer_.String(str);
  }

  bool StartObject() override {
    return writer_.StartObject();
  }

  bool Key(const Ch *str, rapidjson::SizeType length, bool copy = false) override {
    return writer_.Key(str, length, copy);
  }

  bool Key(const std::basic_string<Ch> &str) override {
    return writer_.Key(str);
  }

  bool EndObject(rapidjson::SizeType memberCount = 0) override {
    return writer_.EndObject(memberCount);
  }

  bool StartArray() override {
    return writer_.StartArray();
  }

  bool EndArray(rapidjson::SizeType elementCount = 0) override {
    return writer_.EndArray(elementCount);
  }

  bool String(const Ch *const &str) override {
    return writer_.String(str);
  }

  bool Key(const Ch *const &str) override {
    return writer_.Key(str);
  }

  bool RawValue(const Ch *json, size_t length, rapidjson::Type type) override {
    return writer_.RawValue(json, length, type);
  }

  void Flush() override {
    writer_.Flush();
  }

 private:
  Writer writer_;
};

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_GENERIC_WRITER_H_
