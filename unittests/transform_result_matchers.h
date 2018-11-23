//
// Created by root on 11/23/18.
//

#ifndef RAPIDOSON_TRANSFORM_RESULT_MATCHERS_H
#define RAPIDOSON_TRANSFORM_RESULT_MATCHERS_H

#include <gmock/gmock.h>

#include "transformresult.h"

MATCHER(CheckSucceeded, "") { return arg.has_value() == false; }
MATCHER_P(CheckFailed, message, "") { return arg.has_value() == true && arg.value().message == message; }

MATCHER(TransformSucceeded, "") { return arg.GetFailures().empty(); }
MATCHER_P(TransformFailed, message, "") { return arg.GetFailures().size() == 1 && arg.GetFailures()[0].message == message; }

#endif //RAPIDOSON_TRANSFORM_RESULT_MATCHERS_H
