//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef RAPIDJSON_TRANSFORMRESULT_H
#define RAPIDJSON_TRANSFORMRESULT_H

#include <string>

namespace rapidjson {

    class TransformResult {
    public:
        TransformResult(bool success, const std::string& path, const std::string& message)
                : success_(success)
                , path_(path)
                , message_(message) {}

        bool Success() {
            return success_;
        }

        const std::string & GetPath() {
            return path_;
        }

        const std::string & GetMessage() {
            return message_;
        }

        static TransformResult TRUE;
    private:
        bool success_;
        std::string path_;
        std::string message_;
    };

    TransformResult TransformResult::TRUE(true, "", "");
}  // rapidjson

#endif //RAPIDJSON_TRANSFORMRESULT_H
