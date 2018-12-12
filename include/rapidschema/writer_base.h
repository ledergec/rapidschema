//
// Created by root on 12/12/18.
//

#ifndef INCLUDE_RAPIDSCHEMA_WRITER_BASE_H_
#define INCLUDE_RAPIDSCHEMA_WRITER_BASE_H_

#include <cinttypes>
#include <string>

#include <rapidjson/rapidjson.h>

namespace rapidjson {
class OutputStream;
}  // namespace rapidjson

namespace rapidschema {

/// \brief for documentation of the interface please refer to the documentation of rapidjson::Writer.
class WriterBase {
 public:
  virtual bool IsComplete() const = 0;

  virtual int GetMaxDecimalPlaces() const = 0;

  virtual void SetMaxDecimalPlaces(int maxDecimalPlaces) = 0;

  virtual bool Null() = 0;
  virtual bool Bool(bool b) = 0;
  virtual bool Int(int i) = 0;
  virtual bool Uint(unsigned u) = 0;
  virtual bool Int64(int64_t i64) = 0;
  virtual bool Uint64(uint64_t u64) = 0;

  virtual bool Double(double d) = 0;

  virtual bool RawNumber(const char *str, rapidjson::SizeType length, bool copy = false) = 0;

  virtual bool String(const char *str, rapidjson::SizeType length, bool copy = false) = 0;

  virtual bool String(const std::basic_string<char> &str) = 0;

  virtual bool StartObject() = 0;
  virtual bool Key(const char *str, rapidjson::SizeType length, bool copy = false) = 0;

  virtual bool Key(const std::basic_string<char> &str) = 0;

  virtual bool EndObject(rapidjson::SizeType memberCount = 0) = 0;

  virtual bool StartArray() = 0;
  virtual bool EndArray(rapidjson::SizeType elementCount = 0) = 0;

  virtual bool String(const char *const &str) = 0;

  virtual bool Key(const char *const &str) = 0;

  virtual bool RawValue(const char *json, size_t length, rapidjson::Type type) = 0;

  virtual void Flush() = 0;
};

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_WRITER_BASE_H_
