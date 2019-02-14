// Copyright (C) 2019 Christian Ledergerber

#ifndef RAPIDSCHEMA_OPTIONAL_H
#define RAPIDSCHEMA_OPTIONAL_H

#ifdef RAPIDSCHEMA_CPP_11
#include <absl/types/optional.h>
#else
#include <optional>

namespace absl {
template <typename T>
using optional = std::optional<T>;

using nullopt_t = std::nullopt_t;

 inline constexpr nullopt_t nullopt { std::nullopt };
}
#endif

#endif //RAPIDSCHEMA_OPTIONAL_H
