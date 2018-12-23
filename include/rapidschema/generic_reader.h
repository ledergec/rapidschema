//
// Created by root on 12/17/18.
//

#ifndef INCLUDE_RAPIDSCHEMA_GENERIC_READER_H_
#define INCLUDE_RAPIDSCHEMA_GENERIC_READER_H_

#include "rapidschema/abstract_reader.h"

namespace rapidschema {

template <typename Reader, typename InputStream, typename SourceEncoding = rapidjson::UTF8<>,
    typename TargetEncoding = rapidjson::UTF8<>>
class GenericReader : public AbstractReader<typename SourceEncoding::Ch> {
 public:
  using Ch = typename SourceEncoding::Ch;

  GenericReader(InputStream* is)
      : is_(is) {
    assert(is != nullptr);
  }

  void Init() override {
    reader_.IterativeParseInit();
  }

  bool Next(AbstractHandler<typename SourceEncoding::Ch>* handler) override {
    return reader_.template IterativeParseNext<
        rapidjson::kParseDefaultFlags, InputStream, AbstractHandler<typename TargetEncoding::Ch>>(*is_, *handler);
  };

  bool HasParseError() override  {
    return reader_.HasParseError();
  }

  bool Complete() override {
    return reader_.IterativeParseComplete();
  };

 private:
  InputStream* is_;
  Reader reader_;
};

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_GENERIC_READER_H_
