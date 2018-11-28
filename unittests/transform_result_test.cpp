#include <gtest/gtest.h>

#include "transform_result_matchers.h"

namespace rapidoson {

    using testing::Test;
    using testing::ElementsAre;

    class TransformResultTest : public Test {
    public:
        TransformResultTest() 
        : failure1_("failure1")
        , failure2_("failure2")
        , result_(failure1_) {}

        Failure failure1_;
        Failure failure2_;
        TransformResult empty_result_;
        TransformResult result_;
    };

    TEST_F(TransformResultTest, WhenCreated_ThenEmpty) {
        ASSERT_TRUE(empty_result_.GetFailures().empty());
    }

    TEST_F(TransformResultTest, WhenNoFailureAppendedToEmptyResult_ThenResultEmpty) {
        empty_result_.Append(std::nullopt);
        ASSERT_TRUE(empty_result_.GetFailures().empty());
    }

    TEST_F(TransformResultTest, WhenFailureAppendedToEmptyResult_ThenResultContainsOnlyTheFailure) {
        empty_result_.Append(std::optional<Failure>(failure1_));
        ASSERT_THAT(empty_result_.GetFailures(), ElementsAre(failure1_));
    }

    TEST_F(TransformResultTest, WhenCreatedWithFailure_ThenResultContainsOnlyTheFailure) {
        ASSERT_THAT(result_.GetFailures(), ElementsAre(failure1_));
    }

    TEST_F(TransformResultTest, WhenFailureAppended_ThenResultContainsBothFailures) {
        result_.Append(failure2_);
        ASSERT_THAT(result_.GetFailures(), ElementsAre(failure1_, failure2_));
    }

    TEST_F(TransformResultTest, WhenResultAppended_ThenResultContainsAllFailures) {
        TransformResult temp(failure2_);
        result_.Append(temp);
        ASSERT_THAT(result_.GetFailures(), ElementsAre(failure1_, failure2_));
    }

    TEST_F(TransformResultTest, WhenEmptyResultAppended_ThenResultUnmodified) {
        result_.Append(empty_result_);
        ASSERT_THAT(result_.GetFailures(), ElementsAre(failure1_));
    }

    TEST_F(TransformResultTest, WhenPathAddedToEmptyPath_ThenNoDotAdded) {
        Failure expected = failure1_;
        expected.SetPath("path");
        result_.AddPath("path");
        ASSERT_THAT(result_.GetFailures(), ElementsAre(expected));
    }

    TEST_F(TransformResultTest, WhenPathAddedToNonEmptyPath_ThenDotAdded) {
        Failure expected = failure1_;
        expected.SetPath("second.first");

        result_.AddPath("first");
        result_.AddPath("second");
        ASSERT_THAT(result_.GetFailures(), ElementsAre(expected));
    }
}