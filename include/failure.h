//
// Created by root on 11/23/18.
//

#ifndef RAPIDSCHEMA_FAILURE_H
#define RAPIDSCHEMA_FAILURE_H

#include <string>

namespace rapidschema {

    struct Failure {
        Failure() = default;

        explicit Failure(const std::string& path, const std::string& mes)
                : path_(path)
                , message_(mes) {}

        explicit Failure(const std::string& mes)
        : message_(mes) {}

        const std::string& GetPath() const {
            return path_;
        }

        const void SetPath(const std::string& path) {
            path_ = path;
        }

        const std::string& GetMessage() const {
            return message_;
        }

        std::string path_;
        std::string message_;
    };

    static bool operator==(const Failure & lhs, const Failure& rhs) {
        return lhs.GetMessage() == rhs.GetMessage() && lhs.GetPath() == rhs.GetPath();
    }
}

#endif //RAPIDSCHEMA_FAILURE_H
