//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef INCLUDE_RAPIDSCHEMA_UTILS_H_
#define INCLUDE_RAPIDSCHEMA_UTILS_H_

#include <string>

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

namespace rapidschema {

std::string ValueToString(const rapidjson::Value& document) {
  rapidjson::StringBuffer buffer;
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
  document.Accept(writer);
  return buffer.GetString();
}

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_UTILS_H_
