// Copyright (C) 2019 Christian Ledergerber

#include <gtest/gtest.h>

#include "rapidschema/meta/type_set.h"

namespace rapidschema {
namespace internal {

static_assert(TypeSet<int, int>::Unique() == false, "TypeSet<int, int>::Unique() should return false because there are "
                                                    "multiple int elements");

static_assert(TypeSet<int, float>::Unique(), "TypeSet<int, float>::Unique() should return true because there are "
                                             "only unique elements");

static_assert(TypeSet<int, float, double, std::nullptr_t>::Unique(), "Only unique types contained");

static_assert(TypeSet<int, float, double, std::nullptr_t>::Contains<double>(), "double is contained");

static_assert(TypeSet<int, float, double, std::nullptr_t>::Contains<int64_t>() == false, "int64_t is not contained");


}  // namespace internal
}  // namespace rapidschema
