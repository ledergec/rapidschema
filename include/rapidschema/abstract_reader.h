//
// Created by root on 12/17/18.
//

#ifndef INCLUDE_RAPIDSCHEMA_ABSTRACT_READER_H_
#define INCLUDE_RAPIDSCHEMA_ABSTRACT_READER_H_

#include <rapidjson/encodings.h>

#include "rapidschema/abstract_handler.h"
#include "rapidschema/abstract_intput_stream.h"

namespace rapidschema {

/// \brief for documentation of the interface please refer to the documentation of rapidjson::GenericReader.
template <typename Ch = char>
class AbstractReader {
 public:
  virtual void Init() = 0;

  virtual bool Next(AbstractHandler<Ch>* handler) = 0;

  virtual bool Complete() = 0;
};

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_ABSTRACT_READER_H_
