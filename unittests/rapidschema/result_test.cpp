// Copyright (C) 2019 Christian Ledergerber

#include <gtest/gtest.h>

#include "rapidschema/transform_result_matchers.h"

namespace rapidschema {

using testing::Test;
using testing::ElementsAre;

class ResultTest : public Test {
 public:
  ResultTest()
      : failure1_("failure1")
      , failure2_("failure2")
      , result_(failure1_) {}

  Failure failure1_;
  Failure failure2_;
  Result empty_result_;
  Result result_;
};

TEST_F(ResultTest, WhenCreated_ThenEmpty) {
  ASSERT_TRUE(empty_result_.GetFailures().empty());
}

TEST_F(ResultTest, WhenNoFailureAppendedToEmptyResult_ThenResultEmpty) {
  empty_result_.Append(std::nullopt);
  ASSERT_TRUE(empty_result_.GetFailures().empty());
}

TEST_F(ResultTest, WhenFailureAppendedToEmptyResult_ThenResultContainsOnlyTheFailure) {
  empty_result_.Append(std::optional<Failure>(failure1_));
  ASSERT_THAT(empty_result_.GetFailures(), ElementsAre(failure1_));
}

TEST_F(ResultTest, WhenCreatedWithFailure_ThenResultContainsOnlyTheFailure) {
  ASSERT_THAT(result_.GetFailures(), ElementsAre(failure1_));
}

TEST_F(ResultTest, WhenFailureAppended_ThenResultContainsBothFailures) {
  result_.Append(failure2_);
  ASSERT_THAT(result_.GetFailures(), ElementsAre(failure1_, failure2_));
}

TEST_F(ResultTest, WhenResultAppended_ThenResultContainsAllFailures) {
  Result temp(failure2_);
  result_.Append(temp);
  ASSERT_THAT(result_.GetFailures(), ElementsAre(failure1_, failure2_));
}

TEST_F(ResultTest, WhenEmptyResultAppended_ThenResultUnmodified) {
  result_.Append(empty_result_);
  ASSERT_THAT(result_.GetFailures(), ElementsAre(failure1_));
}

TEST_F(ResultTest, WhenPathAddedToEmptyPath_ThenNoDotAdded) {
  Failure expected = failure1_;
  expected.SetPath("path");
  result_.AddPath("path");
  ASSERT_THAT(result_.GetFailures(), ElementsAre(expected));
}

TEST_F(ResultTest, WhenPathAddedToNonEmptyPath_ThenDotAdded) {
  Failure expected = failure1_;
  expected.SetPath("second.first");

  result_.AddPath("first");
  result_.AddPath("second");
  ASSERT_THAT(result_.GetFailures(), ElementsAre(expected));
}

}  // namespace rapidschema
