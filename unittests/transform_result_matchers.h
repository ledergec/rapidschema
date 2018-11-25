//
// Created by root on 11/23/18.
//

#ifndef RAPIDOSON_TRANSFORM_RESULT_MATCHERS_H
#define RAPIDOSON_TRANSFORM_RESULT_MATCHERS_H

#include <gmock/gmock.h>

#include "failure.h"
#include "transform_result.h"
#include "ostream_operators.h"

MATCHER(CheckSucceeded, "") {
    return arg.has_value() == false;
}

MATCHER_P(CheckFailed, message, "") {
    if (arg.has_value() == false) {
        std::cout << "Expected failure but was success" << std::endl;
        return false;
    }
    bool result = arg.value().message == message;
    if (result == false) {
        std::cout << arg << std::endl;
    }
    return result;
}

MATCHER(TransformSucceeded, "") {
    return arg.Success();
}

MATCHER_P(TransformFailed, message, "") {
    return arg.GetFailures().size() == 1 &&
            arg.GetFailures()[0].message == message;
}

#endif //RAPIDOSON_TRANSFORM_RESULT_MATCHERS_H
