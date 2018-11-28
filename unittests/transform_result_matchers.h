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
    bool result = arg.value().GetMessage() == message;
    if (result == false) {
        std::cout << arg << std::endl;
    }
    return result;
}

MATCHER(TransformSucceeded, "") {
    return arg.Success();
}

MATCHER_P(TransformFailed, message, "") {
    if (arg.GetFailures().size() != 1) {
        std::cout << "Expected one failure, but was " << arg.GetFailures().size() << std::endl;
        return false;
    }
    if(arg.GetFailures()[0].GetMessage().compare(message) != 0) {
        std::cout << "Expected message: \"" << message << "\" actual message: \"" << arg.GetFailures()[0] << "\"" << std::endl;
        return false;
    }
    return true;
}

#endif //RAPIDOSON_TRANSFORM_RESULT_MATCHERS_H
