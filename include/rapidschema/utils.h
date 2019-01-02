//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef INCLUDE_RAPIDSCHEMA_UTILS_H_
#define INCLUDE_RAPIDSCHEMA_UTILS_H_

#include <string>

#include <rapidjson/error/en.h>

namespace rapidschema {
namespace internal {

class Utils {
 public:
  template <typename Ch = char>
  static TransformResult ParseSyntaxError(AbstractReader<Ch> *reader) {
    return TransformResult(
        Failure(fmt::format("Encountered the following json syntax error at offset {}: {}",
                            static_cast<unsigned>(reader->GetErrorOffset()),
                            rapidjson::GetParseError_En(reader->GetParseErrorCode()))));
  }
};

}  // namespace internal
}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_UTILS_H_
