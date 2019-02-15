// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_DEFAULT_VALUE_H_
#define INCLUDE_RAPIDSCHEMA_DEFAULT_VALUE_H_

#include "rapidschema/value.h"
#include "rapidschema/result.h"

namespace rapidschema {

template<typename Ch, typename T, template<typename> class ... Constraints>
class GenericDefaultValue : public GenericValue<Ch, T, Constraints...> {
 public:
  Result HandleMissing() const override {
    return Result();
  }

  using GenericValue<Ch, T, Constraints...>::operator=;
};

template <typename T, template<typename> class ... Constraints>
using DefaultValue = GenericDefaultValue<char, T, Constraints...>;

}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_DEFAULT_VALUE_H_
