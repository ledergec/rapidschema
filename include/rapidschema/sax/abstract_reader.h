//
// Created by root on 12/17/18.
//

#ifndef INCLUDE_RAPIDSCHEMA_SAX_ABSTRACT_READER_H_
#define INCLUDE_RAPIDSCHEMA_SAX_ABSTRACT_READER_H_

#include <rapidjson/encodings.h>

#include "rapidschema/sax/abstract_handler.h"

namespace rapidschema {

/// \brief for documentation of the interface please refer to the documentation of rapidjson::GenericReader.
template <typename Ch = char>
class AbstractReader {
 public:
  virtual void Init() = 0;

  virtual bool Next(AbstractHandler<Ch>* handler) = 0;

  virtual bool HasParseError() = 0;

  virtual size_t GetErrorOffset() = 0;

  virtual rapidjson::ParseErrorCode GetParseErrorCode() = 0;

  virtual void StorePoint() = 0;

  virtual void RestToStorePoint() = 0;

  virtual void ClearStorePoint() = 0;

  virtual bool Complete() = 0;
};

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_SAX_ABSTRACT_READER_H_
