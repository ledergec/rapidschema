//
// Created by root on 11/24/18.
//

#ifndef INCLUDE_RAPIDSCHEMA_OSTREAM_OPERATORS_H_
#define INCLUDE_RAPIDSCHEMA_OSTREAM_OPERATORS_H_

#include <iostream>
#include <optional>

#include "rapidschema/failure.h"
#include "rapidschema/transform_result.h"

namespace rapidschema {

inline std::ostream &operator<<(std::ostream &stream, const Failure& failure) {
    stream << "Failure: [message = " << failure.GetMessage() << ", path = " << failure.GetPath() << "]";
    return stream;
}

inline std::ostream &operator<<(std::ostream &stream, const std::optional<Failure>& failure) {
    if (failure.has_value()) {
        stream << failure.value();
    } else {
        stream << "Success";
    }
    return stream;
}

inline std::ostream &operator<<(std::ostream &stream, const TransformResult& result) {
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

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_OSTREAM_OPERATORS_H_
