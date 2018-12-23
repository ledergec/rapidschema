//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef INCLUDE_RAPIDSCHEMA_CONFIGNODE_H_
#define INCLUDE_RAPIDSCHEMA_CONFIGNODE_H_

#include <string>
#include <vector>

#include <fmt/format.h>

#include "rapidschema/config.h"
#include "rapidschema/rapidjson_type_to_string.h"
#include "rapidschema/transform_result.h"

namespace rapidschema {

template<typename Ch = char>
class GenericNode;

template <typename Ch>
class NodeHandler : public AbstractHandler<Ch> {
 public:
  NodeHandler(AbstractReader<Ch> * reader,
              GenericNode<Ch> * node,
              const std::map<std::basic_string<Ch>, const GenericConfig<Ch>*>& members)
      : finished_(false)
      , unexpected_member_(false)
      , reader_(reader)
      , node_(node)
      , members_(members)
      , encountered_members_(0) {
    assert(reader != nullptr);
    assert(node != nullptr);
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

  bool RawNumber(const Ch* str, rapidjson::SizeType length, bool copy) override {
    assert(false);
    finished_ = true;
    return true;
  }

  bool String(const Ch* str, rapidjson::SizeType length, bool copy) override {
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

  bool Key(const Ch* str, rapidjson::SizeType length, bool copy) override {
    std::basic_string<Ch> key = std::string(str, length);
    if (members_.find(key) != members_.end()) {
      result_.Append(const_cast<GenericConfig<Ch>*>(members_.at(key))->Parse(reader_));
      member_parsed_[key] = true;
      encountered_members_++;
    } else {
      result_.Append(node_->HandleUnexpectedMember(key));
      unexpected_member_ = true;
    }
    return true;
  }

  bool EndObject(rapidjson::SizeType memberCount) override {
    if (encountered_members_ < members_.size()) {
      for (const auto & pair : members_) {
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

  const TransformResult & GetResult() const {
    return result_;
  }

 private:
  bool finished_;
  bool unexpected_member_;
  AbstractReader<Ch> * reader_;
  GenericNode<Ch>* node_;
  const std::map<std::basic_string<Ch>, const GenericConfig<Ch>*>& members_;
  std::unordered_map<std::basic_string<Ch>, bool> member_parsed_;
  size_t encountered_members_;
  TransformResult result_;
};

template<typename Ch>
class GenericNode : public GenericConfig<Ch> {
 public:
  using CharType = Ch;

  GenericNode()
    : mapping_initialized_(false) {}

  GenericNode(const GenericNode<Ch>& other)
    : mapping_initialized_(false) {}

  GenericNode(GenericNode<Ch>&& other)
      : mapping_initialized_(false) {}

  GenericNode & operator= (const GenericNode & other) {
    if (this != &other) {
      mapping_initialized_ = false;
      name_config_mapping_ = std::map<std::basic_string<Ch>, const GenericConfig<Ch>*>();
    }
    return *this;
  }

  TransformResult Parse(AbstractReader<Ch> * reader) override {
    UpdateMapping();

    NodeHandler<Ch> handler(reader, this, name_config_mapping_);
    while (handler.IsFinished() == false && reader->HasParseError() == false) {
      reader->Next(&handler);
    }
    if (reader->HasParseError()) {
      // TODO(cledergerber) convert rapidjson message to string
      return TransformResult(Failure(fmt::format("Encountered errors while parsing.")));
    }
    return handler.GetResult();
  }

  TransformResult Parse(const rapidjson::Value & document) override {
    UpdateMapping();

    if (document.IsObject() == false) {
      TransformResult(Failure(fmt::format("Expected object but was: {} ",
                                          JsonTypeToString(document.GetType()))));
    }

    TransformResult result;
    for (auto pair : name_config_mapping_) {
      if (document.HasMember(pair.first.c_str()) == false) {
        result.Append(Failure(fmt::format("Missing member: \"{}\"", pair.first)));
        continue;
      }

      auto tmp = const_cast<Config*>(pair.second)->Parse(document.FindMember(pair.first.c_str())->value);
      if (tmp.Success() == false) {
        tmp.AddPath(pair.first);
        result.Append(tmp);
      }
    }

    return result;
  }

  TransformResult Validate() const override {
    UpdateMapping();

    TransformResult result;
    for (auto pair : name_config_mapping_) {
      result.Append(pair.second->Validate());
    }

    return result;
  }

  void Serialize(AbstractWriter<Ch>* writer) const override {
    UpdateMapping();

    writer->StartObject();
    for (const auto & pair : name_config_mapping_) {
      writer->Key(pair.first.c_str());
      pair.second->Serialize(writer);
    }
    writer->EndObject();
  }

  TransformResult HandleUnexpectedMember(const std::basic_string<Ch>& key) {
    return TransformResult();
  }

  TransformResult HandleMissing() const override {
    return FailResult("is missing");
  }

 protected:
  virtual std::map<std::basic_string<Ch>, const GenericConfig<Ch>*> CreateMemberMapping() const = 0;

 private:
  void UpdateMapping() const {
    if (mapping_initialized_ == false) {
      name_config_mapping_ = CreateMemberMapping();
      mapping_initialized_ = true;
    }
  }

  mutable bool mapping_initialized_;
  mutable std::map<std::basic_string<Ch>, const GenericConfig<Ch>*> name_config_mapping_;
};

using Node = GenericNode<>;

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_CONFIGNODE_H_
