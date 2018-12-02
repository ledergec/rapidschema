//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef RAPIDSCHEMA_UTILS_H
#define RAPIDSCHEMA_UTILS_H

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

}  // rapidjson

#endif //RAPIDSCHEMA_UTILS_H
