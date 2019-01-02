//
// Created by root on 12/31/18.
//

#ifndef INCLUDE_RAPIDSCHEMA_SAX_SKIP_HANDLER_H_
#define INCLUDE_RAPIDSCHEMA_SAX_SKIP_HANDLER_H_

namespace rapidschema {

template<typename Ch>
class SkipHandler : public AbstractHandler<Ch> {
 public:
  SkipHandler()
      : called_(false)
      , object_count_(0)
      , array_count_(0) {}

  bool Null() override {
    called_ = true;
    return true;
  }

  bool Bool(bool b) override {
    called_ = true;
    return true;
  }

  bool Int(int i) override {
    called_ = true;
    return true;
  }

  bool Uint(unsigned i) override {
    called_ = true;
    return true;
  }

  bool Int64(int64_t i) override {
    called_ = true;
    return true;
  }

  bool Uint64(uint64_t i) override {
    called_ = true;
    return true;
  }

  bool Double(double d) override {
    called_ = true;
    return true;
  }

  bool RawNumber(const Ch *str, rapidjson::SizeType length, bool copy) override {
    called_ = true;
    return true;
  }

  bool String(const Ch *str, rapidjson::SizeType length, bool copy) override {
    called_ = true;
    return true;
  }

  bool StartObject() override {
    called_ = true;
    object_count_++;
    return true;
  }

  bool Key(const Ch *str, rapidjson::SizeType length, bool copy) override {
    called_ = true;
    return true;
  }

  bool EndObject(rapidjson::SizeType memberCount) override {
    object_count_--;
    return true;
  }

  bool StartArray() override {
    called_ = true;
    array_count_++;
    return true;
  }

  bool EndArray(rapidjson::SizeType elementCount) override {
    array_count_--;
    return true;
  }

  bool IsFinished() const {
    return called_ && object_count_ == 0 && array_count_ == 0;
  }

 private:
  bool called_;
  uint32_t object_count_;
  uint32_t array_count_;
};

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_SAX_SKIP_HANDLER_H_
