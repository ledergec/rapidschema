//
// Created by root on 12/17/18.
//

#ifndef INCLUDE_RAPIDSCHEMA_GENERIC_INPUT_STREAM_H_
#define INCLUDE_RAPIDSCHEMA_GENERIC_INPUT_STREAM_H_

#include <rapidjson/encodings.h>

#include "rapidschema/abstract_intput_stream.h"

namespace rapidschema {

/// \brief for documentation of the interface please refer to the documentation of rapidjson::Writer.
template <typename InputStream, typename SourceEncoding = rapidjson::UTF8<>>
class GenericInputStream : public AbstractInputStream<SourceEncoding> {
 public:
  using Ch = typename SourceEncoding::Ch;

  Ch Peek() const override {
    return is_.Peek();
  };

  Ch Take() override {
    return is_.Take();
  };

  size_t Tell() override {
    return is_.Tell();
  };

 private:
  InputStream is_;
};

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_GENERIC_INPUT_STREAM_H_
