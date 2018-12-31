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
  ObjectHandler(AbstractReader<Ch> *reader,
              GenericObject<Ch> *object,
              const std::map<std::basic_string<Ch>, const GenericConfig<Ch> *> &members)
      : finished_(false),
        unexpected_member_(false),
        reader_(reader),
        object_(object),
        members_(members),
        encountered_members_(0) {
    assert(reader != nullptr);
    assert(object != nullptr);
  }

  bool Null() override {
    if (unexpected_member_) {
      unexpected_member_ = false;
      return true;
    }

    result_ = FailResult("Expected Object, encountered Null");
    finished_ = true;
    return true;
  }

  bool Bool(bool b) override {
    if (unexpected_member_) {
      unexpected_member_ = false;
      return true;
    }

    result_ = FailResult("Expected Object, encountered bool");
    finished_ = true;
    return true;
  }

  bool Int(int i) override {
    if (unexpected_member_) {
      unexpected_member_ = false;
      return true;
    }

    result_ = FailResult("Expected Object, encountered int");
    finished_ = true;
    return true;
  }

  bool Uint(unsigned i) override {
    if (unexpected_member_) {
      unexpected_member_ = false;
      return true;
    }

    result_ = FailResult("Expected Object, encountered uint");
    finished_ = true;
    return true;
  }

  bool Int64(int64_t i) override {
    if (unexpected_member_) {
      unexpected_member_ = false;
      return true;
    }

    result_ = FailResult("Expected Object, encountered int64");
    finished_ = true;
    return true;
  }

  bool Uint64(uint64_t i) override {
    if (unexpected_member_) {
      unexpected_member_ = false;
      return true;
    }

    result_ = FailResult("Expected Object, encountered uint64");
    finished_ = true;
    return true;
  }

  bool Double(double d) override {
    if (unexpected_member_) {
      unexpected_member_ = false;
      return true;
    }

    result_ = FailResult("Expected Object, encountered double");
    finished_ = true;
    return true;
  }

  bool RawNumber(const Ch *str, rapidjson::SizeType length, bool copy) override {
    assert(false);
    finished_ = true;
    return true;
  }

  bool String(const Ch *str, rapidjson::SizeType length, bool copy) override {
    if (unexpected_member_) {
      unexpected_member_ = false;
      return true;
    }

    result_ = FailResult("Expected Object, encountered string");
    finished_ = true;
    return true;
  }

  bool StartObject() override {
    return true;
  }

  bool Key(const Ch *str, rapidjson::SizeType length, bool copy) override {
    std::basic_string<Ch> key = std::string(str, length);
    if (members_.find(key) != members_.end()) {
      result_.Append(const_cast<GenericConfig<Ch> *>(members_.at(key))->Parse(reader_));
      member_parsed_[key] = true;
      encountered_members_++;
    } else {
      result_.Append(object_->HandleUnexpectedMember(key));
      unexpected_member_ = true;
    }
    return true;
  }

  bool EndObject(rapidjson::SizeType memberCount) override {
    if (encountered_members_ < members_.size()) {
      for (const auto &pair : members_) {
        if (member_parsed_[pair.first] == false) {
          TransformResult tmp = pair.second->HandleMissing();
          tmp.AddPath(pair.first);
          result_.Append(tmp);
        }
      }
    }
    finished_ = true;
    return true;
  }

  bool StartArray() override {
    assert(false);
    result_ = FailResult("Expected Object, encountered array");
    return true;
  }

  bool EndArray(rapidjson::SizeType elementCount) override {
    assert(false);
    return false;
  }

  bool IsFinished() {
    return finished_;
  }

  const TransformResult &GetResult() const {
    return result_;
  }

 private:
  bool finished_;
  bool unexpected_member_;
  AbstractReader<Ch> *reader_;
  GenericObject<Ch> *object_;
  const std::map<std::basic_string<Ch>, const GenericConfig<Ch> *> &members_;
  std::unordered_map<std::basic_string<Ch>, bool> member_parsed_;
  size_t encountered_members_;
  TransformResult result_;
};

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_SAX_OBJECT_HANDLER_H_
