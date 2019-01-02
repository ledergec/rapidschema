//
// Created by root on 11/26/18.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <chrono>  // NOLINT(build/c++11)

#include "rapidschema/value.h"
#include "rapidschema/test_utils.h"
#include "rapidschema/transform_result_matchers.h"
#include "rapidschema/type_properties.h"

std::ostream& operator<<(std::ostream& stream, const std::chrono::milliseconds& milliseconds) {
  stream << milliseconds.count() << " [ms]";
  return stream;
}

namespace rapidschema {

template<>
struct TypeProperties<std::chrono::milliseconds> {
  static constexpr JsonType json_type = JsonType::NULLTYPE;

  static constexpr char name[] = "nullptr_t";

  static bool IsType(const rapidjson::Value &value) {
    return value.IsUint64();
  }

  static std::chrono::milliseconds FromJson(const rapidjson::Value &value) {
    return std::chrono::milliseconds(value.GetUint64());
  }

  static void Serialize(const std::chrono::milliseconds& milli, AbstractWriter<> * writer) {
    writer->Int64(milli.count());
  }
};


template<typename Ch>
class ValueHandler<std::chrono::milliseconds, Ch> : public ValueHandlerBase<Ch> {
 public:
  explicit ValueHandler(std::chrono::milliseconds *t)
      : ValueHandlerBase<Ch>("milliseconds")
      , t_(t) {}

  bool Int(int i) override {
    if (this->object_count_ > 0 || this->array_count_ > 0) {
      return true;
    }

    this->finished_ = true;
    *t_ = std::chrono::milliseconds(i);
    return true;
  }

  bool Uint(unsigned i) override {
    if (this->object_count_ > 0 || this->array_count_ > 0) {
      return true;
    }

    this->finished_ = true;
    *t_ = std::chrono::milliseconds(i);
    return true;
  }

  bool Int64(int64_t i) override {
    if (this->object_count_ > 0 || this->array_count_ > 0) {
      return true;
    }

    this->finished_ = true;
    *t_ = std::chrono::milliseconds(i);
    return true;
  }

  bool Uint64(uint64_t i) override {
    if (this->object_count_ > 0 || this->array_count_ > 0) {
      return true;
    }

    this->finished_ = true;
    if (i <= std::numeric_limits<uint64_t>::max()) {
      *t_ = std::chrono::milliseconds(static_cast<int64_t>(i));
    } else {
      this->result_ = FailResult("Expected int64 but was uint64");
    }
    return true;
  }

 private:
  std::chrono::milliseconds *t_;
};


TEST(Int64ConfigValueTest, CanParseCustomType) {
  auto json = R"({"leaf": 123})";
  Value<std::chrono::milliseconds> value;
  auto result = ParseJsonLeaf(json, &value);
  ASSERT_THAT(result, TransformSucceeded());
  ASSERT_EQ(std::chrono::milliseconds(123), value.Get());
}

}  // namespace rapidschema
