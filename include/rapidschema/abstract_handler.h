//
// Created by root on 12/17/18.
//

#ifndef INCLUDE_RAPIDSCHEMA_ABSTRACT_HANDLER_H_
#define INCLUDE_RAPIDSCHEMA_ABSTRACT_HANDLER_H_

#include <rapidjson/rapidjson.h>
#include <rapidjson/encodings.h>

namespace rapidschema {

/// \brief for documentation of the interface please refer to the documentation of rapidjson::Writer.
template <typename TargetEncoding = rapidjson::UTF8<>>
class AbstractHandler {
 public:
  using Ch = typename TargetEncoding::Ch;

  virtual bool Null() = 0;
  virtual bool Bool(bool b) = 0;
  virtual bool Int(int i) = 0;
  virtual bool Uint(unsigned i) = 0;
  virtual bool Int64(int64_t i) = 0;
  virtual bool Uint64(uint64_t i) = 0;
  virtual bool Double(double d) = 0;
  virtual bool RawNumber(const Ch* str, rapidjson::SizeType length, bool copy) = 0;
  virtual bool String(const Ch* str, rapidjson::SizeType length, bool copy) = 0;
  virtual bool StartObject() = 0;
  virtual bool Key(const Ch* str, rapidjson::SizeType length, bool copy) = 0;
  virtual bool EndObject(rapidjson::SizeType memberCount) = 0;
  virtual bool StartArray() = 0;
  virtual bool EndArray(rapidjson::SizeType elementCount) = 0;
};

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_ABSTRACT_HANDLER_H_
