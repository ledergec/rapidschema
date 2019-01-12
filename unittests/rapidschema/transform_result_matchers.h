// Copyright (C) 2019 Christian Ledergerber

#ifndef UNITTESTS_RAPIDSCHEMA_TRANSFORM_RESULT_MATCHERS_H_
#define UNITTESTS_RAPIDSCHEMA_TRANSFORM_RESULT_MATCHERS_H_

#include <gmock/gmock.h>

#include "rapidschema/failure.h"
#include "rapidschema/transform_result.h"
#include "rapidschema/ostream_operators.h"

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

MATCHER_P2(TransformFailed, message, path, "") {
  if (arg.GetFailures().size() != 1) {
    std::cout << "Expected one failure, but was " << arg.GetFailures().size() << std::endl;
    return false;
  }
  if (arg.GetFailures()[0].GetMessage().compare(message) != 0) {
    std::cout << "Expected message: \"" << message << "\" actual message: \""
              << arg.GetFailures()[0] << "\"" << std::endl;
    return false;
  }
  if (arg.GetFailures()[0].GetPath().compare(path) != 0) {
    std::cout << "Expected path: \"" << path << "\" actual path: \"" << arg.GetFailures()[0].GetPath() << "\"" <<
    std::endl;
    return false;
  }
  return true;
}

#endif  // UNITTESTS_RAPIDSCHEMA_TRANSFORM_RESULT_MATCHERS_H_
