//
// Created by root on 12/31/18.
//

#ifndef INCLUDE_RAPIDSCHEMA_SAX_OBJECT_HANDLER_H_
#define INCLUDE_RAPIDSCHEMA_SAX_OBJECT_HANDLER_H_

namespace rapidschema {

template<typename Ch>
class GenericObject;

template<typename Ch>
class ObjectHandler : public AbstractHandler<Ch> {
 public:
  ObjectHandler()
      : finished_(false)
      , has_key_(false)
      , array_count_(0) {}

  bool Null() override {
    if (array_count_ > 0) {
      return true;
    }

    result_ = FailResult("Expected Object, encountered Null");
    finished_ = true;
    return true;
  }

  bool Bool(bool b) override {
    if (array_count_ > 0) {
      return true;
    }

    result_ = FailResult("Expected Object, encountered bool");
    finished_ = true;
    return true;
  }

  bool Int(int i) override {
    if (array_count_ > 0) {
      return true;
    }

    result_ = FailResult("Expected Object, encountered int");
    finished_ = true;
    return true;
  }

  bool Uint(unsigned i) override {
    if (array_count_ > 0) {
      return true;
    }

    result_ = FailResult("Expected Object, encountered uint");
    finished_ = true;
    return true;
  }

  bool Int64(int64_t i) override {
    if (array_count_ > 0) {
      return true;
    }

    result_ = FailResult("Expected Object, encountered int64");
    finished_ = true;
    return true;
  }

  bool Uint64(uint64_t i) override {
    if (array_count_ > 0) {
      return true;
    }

    result_ = FailResult("Expected Object, encountered uint64");
    finished_ = true;
    return true;
  }

  bool Double(double d) override {
    if (array_count_ > 0) {
      return true;
    }

    result_ = FailResult("Expected Object, encountered double");
    finished_ = true;
    return true;
  }

  bool RawNumber(const Ch *str, rapidjson::SizeType length, bool copy) override {
    if (array_count_ > 0) {
      return true;
    }

    assert(false);
    finished_ = true;
    return true;
  }

  bool String(const Ch *str, rapidjson::SizeType length, bool copy) override {
    if (array_count_ > 0) {
      return true;
    }

    result_ = FailResult("Expected Object, encountered string");
    finished_ = true;
    return true;
  }

  bool StartObject() override {
    if (array_count_ > 0) {
      return true;
    }

    has_key_ = false;
    return true;
  }

  bool Key(const Ch *str, rapidjson::SizeType length, bool copy) override {
    if (array_count_ > 0) {
      return true;
    }

    has_key_ = true;
    key_ = std::basic_string<Ch>(str, length);
    return true;
  }

  bool EndObject(rapidjson::SizeType memberCount) override {
    if (array_count_ > 0) {
      return true;
    }

    has_key_ = false;
    finished_ = true;
    return true;
  }

  bool StartArray() override {
    array_count_++;
    has_key_ = false;
    result_ = FailResult("Expected Object, encountered array");
    return true;
  }

  bool EndArray(rapidjson::SizeType elementCount) override {
    array_count_--;
    has_key_ = false;
    return false;
  }

  bool IsFinished() {
    return finished_;
  }

  bool HasKey() const {
    return has_key_;
  }

  const std::basic_string<Ch>& GetKey() const {
    return key_;
  }

  const TransformResult& GetResult() const {
    return result_;
  }

 private:
  bool finished_;
  bool has_key_;
  uint32_t array_count_;
  std::basic_string<Ch> key_;
  TransformResult result_;
};

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_SAX_OBJECT_HANDLER_H_
