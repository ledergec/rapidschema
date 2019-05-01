// Copyright (C) 2019 Christian Ledergerber

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "rapidschema/pointer.h"

namespace rapidschema {

TEST(PointerTest, GivenEqualPointers_ThenEqualsOperatorTrue) {
  ASSERT_EQ(Pointer({"a", "b"}), Pointer({"a", "b"}));
}

TEST(PointerTest, GivenUnequalTokensInPointers_ThenEqualsOperatorFalse) {
  ASSERT_NE(Pointer({"a", "c"}), Pointer({"a", "b"}));
}

TEST(PointerTest, GivenUnequalLengthPointers_ThenEqualsOperatorFalse) {
  ASSERT_NE(Pointer({"a"}), Pointer({"a", "b"}));
}

}  // namespace rapidschema

