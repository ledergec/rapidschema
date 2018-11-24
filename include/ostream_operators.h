//
// Created by root on 11/24/18.
//

#ifndef RAPIDOSON_OSTREAM_OPERATORS_H
#define RAPIDOSON_OSTREAM_OPERATORS_H

#include <optional>

#include "failure.h"
#include "transform_result.h"

namespace rapidoson {

    static std::ostream &operator<<(std::ostream &stream, const std::optional<Failure> &failure) {
        if (failure.has_value()) {
            stream << "Failed with " << failure.value().message << " at " << failure.value().path;
        }
    }

}
#endif //RAPIDOSON_OSTREAM_OPERATORS_H
