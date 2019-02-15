// Copyright (C) 2019 Christian Ledergerber

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "rapidschema/utils/regex.h"

namespace rapidschema {

using testing::Test;
using testing::UnorderedElementsAre;

class RegexTest : public Test {
 public:
  bool IsMatch(const std::string& pattern, const std::string& string) {
    auto regex = Regex<char>::CreateRegex(pattern);
    return Regex<char>::IsCompleteMatch(regex, string);
  }
};

TEST_F(RegexTest, GivenMatchAllRegexThenAnyStringMatched) {
  ASSERT_TRUE(IsMatch(".*", "2435fjioin2359&^%*%"));
}

TEST_F(RegexTest, GivenExactMatchRegexThenExactStringMatchedOnly) {
  ASSERT_TRUE(IsMatch("hallo", "hallo"));
  ASSERT_FALSE(IsMatch("hallo", "hallo1"));
  ASSERT_FALSE(IsMatch("hallo", "halln"));
}

}  // namespace rapidschema
