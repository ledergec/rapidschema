//
// Created by root on 12/31/18.
//

#ifndef INCLUDE_RAPIDSCHEMA_SAX_VALUE_HANDLER_H_
#define INCLUDE_RAPIDSCHEMA_SAX_VALUE_HANDLER_H_

namespace rapidschema {


template<typename Ch>
class ValueHandlerBase : public AbstractHandler<Ch> {
 public:
  explicit ValueHandlerBase(const std::string & expected_type)
      : expected_type_(expected_type)
      , finished_(false)
      , object_count_(0)
      , array_count_(0) {}

  bool Null() override {
    if (object_count_ > 0 || array_count_ > 0) {
      return true;
    }
    finished_ = true;
    result_ = FailResult(fmt::format("Expected {} but was null", expected_type_));
    return true;
  }

  bool Bool(bool b) override {
    if (object_count_ > 0 || array_count_ > 0) {
      return true;
    }
    finished_ = true;
    result_ = FailResult(fmt::format("Expected {} but was bool", expected_type_));
    return true;
  }

  bool Int(int i) override {
    if (object_count_ > 0 || array_count_ > 0) {
      return true;
    }
    finished_ = true;
    result_ = FailResult(fmt::format("Expected {} but was int", expected_type_));
    return true;
  }

  bool Uint(unsigned i) override {
    if (object_count_ > 0 || array_count_ > 0) {
      return true;
    }
    finished_ = true;
    result_ = FailResult(fmt::format("Expected {} but was uint", expected_type_));
    return true;
  }

  bool Int64(int64_t i) override {
    if (object_count_ > 0 || array_count_ > 0) {
      return true;
    }
    finished_ = true;
    result_ = FailResult(fmt::format("Expected {} but was int64", expected_type_));
    return true;
  }

  bool Uint64(uint64_t i) override {
    if (object_count_ > 0 || array_count_ > 0) {
      return true;
    }
    finished_ = true;
    result_ = FailResult(fmt::format("Expected {} but was uint64", expected_type_));
    return true;
  }

  bool Double(double d) override {
    if (object_count_ > 0 || array_count_ > 0) {
      return true;
    }
    finished_ = true;
    result_ = FailResult(fmt::format("Expected {} but was double", expected_type_));
    return true;
  }

  bool RawNumber(const Ch *str, rapidjson::SizeType length, bool copy) override {
    assert(false);
    return true;
  }

  bool String(const Ch *str, rapidjson::SizeType length, bool copy) override {
    if (object_count_ > 0 || array_count_ > 0) {
      return true;
    }
    finished_ = true;
    result_ = FailResult(fmt::format("Expected {} but was string", expected_type_));
    return true;
  }

  bool StartObject() override {
    finished_ = true;
    if (object_count_ == 0 && array_count_ == 0) {
      result_ = FailResult(fmt::format("Expected {} but was object", expected_type_));
    }
    object_count_++;
    return true;
  }

  bool Key(const Ch *str, rapidjson::SizeType length, bool copy) override {
    return true;
  }

  bool EndObject(rapidjson::SizeType memberCount) override {
    object_count_--;
    return true;
  }

  bool StartArray() override {
    finished_ = true;
    if (object_count_ == 0 && array_count_ == 0) {
      result_ = FailResult(fmt::format("Expected {} but was array", expected_type_));
    }
    array_count_++;
    return true;
  }

  bool EndArray(rapidjson::SizeType elementCount) override {
    array_count_--;
    return true;
  }

  bool IsFinished() {
    return finished_ && object_count_ == 0 && array_count_ == 0;
  }

  const TransformResult &GetResult() {
    return result_;
  }

 protected:
  std::string expected_type_;
  TransformResult result_;
  bool finished_;
  unsigned object_count_;
  unsigned array_count_;
};

template<typename Type, typename Ch = char>
class ValueHandler;

template<typename Ch>
class ValueHandler<int, Ch> : public ValueHandlerBase<Ch> {
 public:
  explicit ValueHandler(int *t)
      : ValueHandlerBase<Ch>("int")
      , t_(t) {}

  bool Int(int i) override {
    if (this->object_count_ > 0 || this->array_count_ > 0) {
      return true;
    }

    this->finished_ = true;
    *t_ = i;
    return true;
  }

  bool Uint(unsigned i) override {
    if (this->object_count_ > 0 || this->array_count_ > 0) {
      return true;
    }

    this->finished_ = true;
    if (i <= std::numeric_limits<int>::max()) {
      *t_ = static_cast<int>(i);
    } else {
      this->result_ = FailResult("Expected int but was uint32");
    }
    return true;
  }

  bool Int64(int64_t i) override {
    if (this->object_count_ > 0 || this->array_count_ > 0) {
      return true;
    }

    this->finished_ = true;
    if (std::numeric_limits<int>::min() <= i && i <= std::numeric_limits<int>::max()) {
      *t_ = static_cast<int>(i);
    } else {
      this->result_ = FailResult("Expected int but was int64");
    }
    return true;
  }

  bool Uint64(uint64_t i) override {
    if (this->object_count_ > 0 || this->array_count_ > 0) {
      return true;
    }

    this->finished_ = true;
    if (i <= std::numeric_limits<int>::max()) {
      *t_ = static_cast<int>(i);
    } else {
      this->result_ = FailResult("Expected int but was uint64");
    }
    return true;
  }

 private:
  int *t_;
};

template<typename Ch>
class ValueHandler<unsigned, Ch> : public ValueHandlerBase<Ch> {
 public:
  explicit ValueHandler(unsigned *t)
      : ValueHandlerBase<Ch>("unsigned int")
      , t_(t) {}

  bool Int(int i) override {
    if (this->object_count_ > 0 || this->array_count_ > 0) {
      return true;
    }

    this->finished_ = true;
    if (i >= 0) {
      *t_ = static_cast<unsigned>(i);
    } else {
      this->result_ = FailResult("Expected unsigned int but was int");
    }
    return true;
  }

  bool Uint(unsigned i) override {
    if (this->object_count_ > 0 || this->array_count_ > 0) {
      return true;
    }

    this->finished_ = true;
    *t_ = i;
    return true;
  }

  bool Int64(int64_t i) override {
    if (this->object_count_ > 0 || this->array_count_ > 0) {
      return true;
    }

    this->finished_ = true;
    if (std::numeric_limits<unsigned>::min() <= i && i <= std::numeric_limits<unsigned>::max()) {
      *t_ = static_cast<unsigned>(i);
    } else {
      this->result_ = FailResult("Expected unsigned int but was int64");
    }
    return true;
  }

  bool Uint64(uint64_t i) override {
    if (this->object_count_ > 0 || this->array_count_ > 0) {
      return true;
    }

    this->finished_ = true;
    if (i <= std::numeric_limits<unsigned>::max()) {
      *t_ = static_cast<unsigned>(i);
    } else {
      this->result_ = FailResult("Expected unsigned int but was uint64");
    }
    return true;
  }

 private:
  unsigned *t_;
};

template<typename Ch>
class ValueHandler<int64_t, Ch> : public ValueHandlerBase<Ch> {
 public:
  explicit ValueHandler(int64_t *t)
      : ValueHandlerBase<Ch>("int64")
      , t_(t) {}

  bool Int(int i) override {
    if (this->object_count_ > 0 || this->array_count_ > 0) {
      return true;
    }

    this->finished_ = true;
    *t_ = i;
    return true;
  }

  bool Uint(unsigned i) override {
    if (this->object_count_ > 0 || this->array_count_ > 0) {
      return true;
    }

    this->finished_ = true;
    *t_ = i;
    return true;
  }

  bool Int64(int64_t i) override {
    if (this->object_count_ > 0 || this->array_count_ > 0) {
      return true;
    }

    this->finished_ = true;
    *t_ = i;
    return true;
  }

  bool Uint64(uint64_t i) override {
    if (this->object_count_ > 0 || this->array_count_ > 0) {
      return true;
    }

    this->finished_ = true;
    if (i <= std::numeric_limits<int64_t>::max()) {
      *t_ = static_cast<int32_t>(i);
    } else {
      this->result_ = FailResult("Expected int64 but was uint64");
    }
    return true;
  }

 private:
  int64_t *t_;
};

template<typename Ch>
class ValueHandler<uint64_t, Ch> : public ValueHandlerBase<Ch> {
 public:
  explicit ValueHandler(uint64_t * t)
      : ValueHandlerBase<Ch>("uint64")
      , t_(t) {}

  bool Int(int i) override {
    if (this->object_count_ > 0 || this->array_count_ > 0) {
      return true;
    }

    this->finished_ = true;
    if (i >= 0) {
      *t_ = i;
    } else {
      this->result_ = FailResult("Expected uint64 but was int");
    }
    return true;
  }

  bool Uint(unsigned i) override {
    if (this->object_count_ > 0 || this->array_count_ > 0) {
      return true;
    }

    this->finished_ = true;
    *t_ = i;
    return true;
  }

  bool Int64(int64_t i) override {
    if (this->object_count_ > 0 || this->array_count_ > 0) {
      return true;
    }

    this->finished_ = true;
    if (i >= 0 && i <= std::numeric_limits<uint64_t>::max()) {
      *t_ = static_cast<uint64_t>(i);
    } else {
      this->result_ = FailResult("Expected uint64 but was int64");
    }
    return true;
  }

  bool Uint64(uint64_t i) override {
    if (this->object_count_ > 0 || this->array_count_ > 0) {
      return true;
    }

    this->finished_ = true;
    *t_ = i;
    return true;
  }

 private:
  uint64_t * t_;
};

template<typename Ch>
class ValueHandler<double, Ch> : public ValueHandlerBase<Ch> {
 public:
  explicit ValueHandler(double *t)
      : ValueHandlerBase<Ch>("double")
      , t_(t) {}

  bool Int(int i) override {
    if (this->object_count_ > 0 || this->array_count_ > 0) {
      return true;
    }

    this->finished_ = true;
    *t_ = static_cast<double>(i);
    return true;
  }

  bool Uint(unsigned i) override {
    if (this->object_count_ > 0 || this->array_count_ > 0) {
      return true;
    }

    this->finished_ = true;
    *t_ = static_cast<double>(i);
    return true;
  }

  bool Int64(int64_t i) override {
    if (this->object_count_ > 0 || this->array_count_ > 0) {
      return true;
    }

    this->finished_ = true;
    *t_ = static_cast<double>(i);
    return true;
  }

  bool Uint64(uint64_t i) override {
    if (this->object_count_ > 0 || this->array_count_ > 0) {
      return true;
    }

    this->finished_ = true;
    *t_ = static_cast<double>(i);
    return true;
  }

  bool Double(double d) override {
    if (this->object_count_ > 0 || this->array_count_ > 0) {
      return true;
    }

    this->finished_ = true;
    *t_ = d;
    return true;
  }

 private:
  double *t_;
};

template<typename Ch>
class ValueHandler<std::string, Ch> : public ValueHandlerBase<Ch> {
 public:
  explicit ValueHandler(std::string * t)
      : ValueHandlerBase<Ch>("string")
      , t_(t) {}

  bool String(const Ch *str, rapidjson::SizeType length, bool copy) override {
    if (this->object_count_ > 0 || this->array_count_ > 0) {
      return true;
    }

    this->finished_ = true;
    *t_ = std::string(str, length);
    return true;
  }

 private:
  std::string * t_;
};

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_SAX_VALUE_HANDLER_H_
