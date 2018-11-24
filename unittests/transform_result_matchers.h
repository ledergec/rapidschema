//
// Created by root on 11/23/18.
//

#ifndef RAPIDOSON_TRANSFORM_RESULT_MATCHERS_H
#define RAPIDOSON_TRANSFORM_RESULT_MATCHERS_H

#include <gmock/gmock.h>

#include "failure.h"
#include "failure_collection.h"
#include "ostream_operators.h"

MATCHER(CheckSucceeded, "") {
    return arg.has_value() == false;
}

MATCHER_P(CheckFailed, message, "") {
    bool result = arg.has_value() == true && arg.value().message == message;
    if (result == false) {
        std::cout << arg << std::endl;
    }
    return result;
}

MATCHER(TransformSucceeded, "") {
    return arg.has_value() == false;
}

MATCHER_P(TransformFailed, message, "") {
    return arg.has_value() &&
            arg.value().GetFailures().size() == 1 &&
            arg.value().GetFailures()[0].message == message;
}

#endif //RAPIDOSON_TRANSFORM_RESULT_MATCHERS_H
