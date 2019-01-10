//
// Created by root on 12/17/18.
//

#ifndef INCLUDE_RAPIDSCHEMA_SAX_GENERIC_READER_H_
#define INCLUDE_RAPIDSCHEMA_SAX_GENERIC_READER_H_

#include "rapidschema/sax/abstract_reader.h"

namespace rapidschema {

template <typename Reader, typename InputStream, typename SourceEncoding = rapidjson::UTF8<>,
    typename TargetEncoding = rapidjson::UTF8<>>
class GenericReader : public AbstractReader<typename SourceEncoding::Ch> {
 public:
  using Ch = typename SourceEncoding::Ch;

  explicit GenericReader(InputStream* is)
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

  size_t GetErrorOffset() override {
    return reader_.GetErrorOffset();
  }

  rapidjson::ParseErrorCode GetParseErrorCode() {
    return reader_.GetParseErrorCode();
  }

  void StorePoint() override {
    // TODO(cledergerber) after this call all event should be recorded, todo this a forwarding / recording handler is
    //  required
  }

  void RestToStorePoint() override {
    // TODO(cledergerber) after this call all recorded events should be replayed, once all have been replayed new events
    // should be recorded
  }

  void ClearStorePoint() override {
    // TODO(cledergerber) after this no recording is needed anymore
  }

  bool Complete() override {
    return reader_.IterativeParseComplete();
  };

 private:
  InputStream* is_;
  Reader reader_;
};

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_SAX_GENERIC_READER_H_
