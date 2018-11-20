//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef RAPIDJSON_UTILS_H
#define RAPIDJSON_UTILS_H

#include <rapidjson/stringbuffer.h>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>

namespace rapidoson {

    std::string ValueToString(const rapidjson::Value& document) {
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);
        return buffer.GetString();
    }

}  // rapidjson

#endif //RAPIDJSON_UTILS_H
