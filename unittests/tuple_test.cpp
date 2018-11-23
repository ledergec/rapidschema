
#include <tuple>
#include <type_traits>

#include <gtest/gtest.h>

namespace rapidoson {

    class A {};
    class B {};
    class C {};

    TEST(TupleTest, TestSizeOfEmptyTuple) {
        ASSERT_EQ(1, sizeof(std::tuple<A, B>));
        ASSERT_EQ(1, sizeof(std::tuple<A, B, C>));
        static_assert(std::is_same<A, typename std::tuple_element<0, std::tuple<A, B>>::type>::value, "");

        using test_type = std::enable_if<std::is_same<A, typename std::tuple_element<0, std::tuple<A, B>>::type>::value>::type;
        static_assert(std::is_same<A, typename std::tuple_element<0, std::tuple<A, B>>::type>::value, "");
    }
}