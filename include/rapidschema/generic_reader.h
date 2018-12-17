//
// Created by root on 12/17/18.
//

#ifndef INCLUDE_RAPIDSCHEMA_GENERIC_READER_H_
#define INCLUDE_RAPIDSCHEMA_GENERIC_READER_H_

#include "rapidschema/abstract_reader.h"

namespace rapidschema {

template <typename Reader, typename SourceEncoding = rapidjson::UTF8<>, typename TargetEncoding = rapidjson::UTF8<>>
class GenericReader : public AbstractReader<TargetEncoding> {
 public:
  using Ch = typename SourceEncoding::Ch;

  GenericReader(AbstractInputStream<SourceEncoding>* is)
      : is_(is) {}

  void Init() override {
    reader_.IterativeParseInit();
  }

  bool Next(AbstractHandler<TargetEncoding>* handler) override {
    return reader_.IterativeParseNext(*is_, *handler);
  };

  bool Complete() override {
    return reader_.Complete();
  };

 private:
  AbstractInputStream<SourceEncoding>* is_;
  Reader reader_;
};

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_GENERIC_READER_H_
