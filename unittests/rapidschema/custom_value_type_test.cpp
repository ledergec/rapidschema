//
// Created by root on 11/26/18.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <chrono>  // NOLINT(build/c++11)

#include "rapidschema/configvalue.h"
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

template <typename Ch>
class ValueHandler<std::chrono::milliseconds, Ch> : public AbstractHandler<Ch> {
 public:
  explicit ValueHandler(std::chrono::milliseconds * t)
      : t_(t) {}

  bool Null() override {
    return false;
  }

  bool Bool(bool b) override {
    return false;
  }

  bool Int(int i) override {
    if (i < 0) {
      return false;
    } else {
      *t_ = std::chrono::milliseconds(static_cast<uint64_t>(i));
      return true;
    }
  }

  bool Uint(unsigned i) override {
    *t_ = std::chrono::milliseconds(i);
    return true;
  }

  bool Int64(int64_t i) override {
    if (i < 0) {
      return false;
    } else {
      *t_ = std::chrono::milliseconds(static_cast<uint64_t>(i));
      return true;
    }
  }

  bool Uint64(uint64_t i) override {
    *t_ = std::chrono::milliseconds(i);
    return true;
  }

  bool Double(double d) override {
    return false;
  }

  bool RawNumber(const Ch* str, rapidjson::SizeType length, bool copy) override {
    assert(false);
    return false;
  }

  bool String(const Ch* str, rapidjson::SizeType length, bool copy) override {
    return false;
  }

  bool StartObject() override {
    return false;
  }

  bool Key(const Ch* str, rapidjson::SizeType length, bool copy) override {
    return false;
  }

  bool EndObject(rapidjson::SizeType memberCount) override {
    return false;
  }

  bool StartArray() override {
    return false;
  }

  bool EndArray(rapidjson::SizeType elementCount) override {
    return false;
  }

 private:
  std::chrono::milliseconds * t_;
};

TEST(Int64ConfigValueTest, CanParseCustomType) {
  auto json = R"({"leaf": 123})";
  Value<std::chrono::milliseconds> value;
  auto result = ParseJsonLeaf(json, &value);
  ASSERT_THAT(result, TransformSucceeded());
  ASSERT_EQ(std::chrono::milliseconds(123), value.Get());
}

}  // namespace rapidschema
