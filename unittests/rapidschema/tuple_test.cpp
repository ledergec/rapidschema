// Copyright (C) 2019 Christian Ledergerber

#include <gtest/gtest.h>

#include <tuple>
#include <type_traits>

namespace rapidschema {

class A {};
class B {};
class C {};

TEST(TupleTest, TestSizeOfEmptyTuple) {
  ASSERT_EQ(1, sizeof(std::tuple<A>));
  ASSERT_EQ(1, sizeof(std::tuple<A, B>));
  ASSERT_EQ(1, sizeof(std::tuple<A, B, C>));
  static_assert(std::is_same<A, typename std::tuple_element<0, std::tuple<A, B>>::type>::value, "");

  A a = std::get<0>(std::tuple<A>());
  (void) a;

  static_assert(std::is_same<A, typename std::tuple_element<0, std::tuple<A, B>>::type>::value, "");
}

}  // namespace rapidschema
