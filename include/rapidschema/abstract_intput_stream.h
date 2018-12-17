//
// Created by root on 12/17/18.
//

#ifndef INCLUDE_RAPIDSCHEMA_ABSTRACT_INTPUT_STREAM_H_
#define INCLUDE_RAPIDSCHEMA_ABSTRACT_INTPUT_STREAM_H_

#include <rapidjson/encodings.h>

namespace rapidschema {

/// \brief for documentation of the interface please refer to the documentation of rapidjson::Writer.
template <typename SourceEncoding = rapidjson::UTF8<>>
class AbstractInputStream {
 public:
  using Ch = typename SourceEncoding::Ch;

  virtual Ch Peek() const = 0;
  virtual Ch Take() = 0;
  virtual size_t Tell() = 0;
};

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_ABSTRACT_INTPUT_STREAM_H_
