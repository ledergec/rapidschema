#include <gtest/gtest.h>

#include "rapidschema/meta/json_type_set.h"

namespace rapidschema {
namespace internal {

using IntStringBool = JsonTypeSet<int, std::string, bool>;
using IntFloatBool = JsonTypeSet<int, float, bool>;

static_assert(IntFloatBool::Unique() == false, "IntFloatBool::Unique() should return false because there are "
                                               "multiple numeric elements");

static_assert(IntStringBool::Unique(), "IntStringBool::Unique() should return true because all elements map to "
                                       "different JsonType");

static_assert(IntStringBool::Contains<float>(), "IntStringBool::Contains<float>() should return true because"
                                                "it contains a numeric (e.g. int) and float is numeric");

static_assert(IntStringBool::Contains<std::nullptr_t>() == false, "IntStringBool::Contains<std::nullptr_t>() "
                                                                  "should return false because none of the "
                                                                  "contained types map to JsonType::NULL");

}  // namespace internal
}  // namespace rapidschema
