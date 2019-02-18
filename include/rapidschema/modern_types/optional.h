// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_MODERN_TYPES_OPTIONAL_H_
#define INCLUDE_RAPIDSCHEMA_MODERN_TYPES_OPTIONAL_H_

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

#endif  // INCLUDE_RAPIDSCHEMA_MODERN_TYPES_OPTIONAL_H_
