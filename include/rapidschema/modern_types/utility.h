// Copyright (C) 2019 Christian Ledergerber

#ifndef RAPIDSCHEMA_TUPLE_H
#define RAPIDSCHEMA_TUPLE_H

#ifdef RAPIDSCHEMA_CPP_11
#include <absl/utility/utility.h>
#else
#include <utility>

namespace absl {
template <size_t ... Indices>
using index_sequence = std::index_sequence<Indices...>;

template <size_t N>
using make_index_sequence = std::make_index_sequence<N>;

template <typename TupleT>
using remove_reference_t = std::remove_reference_t<TupleT>;
}
#endif

#endif //RAPIDSCHEMA_TUPLE_H
