//
// Created by root on 11/24/18.
//

#ifndef RAPIDSCHEMA_OSTREAM_OPERATORS_H
#define RAPIDSCHEMA_OSTREAM_OPERATORS_H

#include <iostream>
#include <optional>

#include "failure.h"
#include "transform_result.h"

namespace rapidschema {

    static std::ostream &operator<<(std::ostream &stream, const Failure& failure) {
        stream << "Failure: [message = " << failure.GetMessage() << ", path = " << failure.GetPath() << "]";
        return stream;
    }

    static std::ostream &operator<<(std::ostream &stream, const std::optional<Failure>& failure) {
        if (failure.has_value()) {
            stream << failure.value();
        } else {
            stream << "Success";
        }
        return stream;
    }

    static std::ostream &operator<<(std::ostream &stream, const TransformResult& result) {
        if (result.Success()) {
            stream << "Success" << std::endl;
        } else {
            stream << "Failed with the following failures" << std::endl;
            for (const auto& failure : result.GetFailures()) {
                stream << failure << std::endl;
            }
        }
        return stream;
    }

}

#endif //RAPIDSCHEMA_OSTREAM_OPERATORS_H
