//
// Created by root on 11/23/18.
//

#ifndef RAPIDOSON_FAILURE_H
#define RAPIDOSON_FAILURE_H

#include <string>

namespace rapidoson {

    struct Failure {
        Failure() {}

        explicit Failure(const std::string& mes) {
            message = mes;
        }

        std::string message;
        std::string path;
    };

    static bool operator==(const Failure & lhs, const Failure& rhs) {
        return lhs.message == rhs.message && rhs.path == rhs.path;
    }
}

#endif //RAPIDOSON_FAILURE_H