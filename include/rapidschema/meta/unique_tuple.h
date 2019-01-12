// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_META_UNIQUE_TUPLE_H_
#define INCLUDE_RAPIDSCHEMA_META_UNIQUE_TUPLE_H_

#include <cassert>
#include <tuple>

#include "rapidschema/concepts/requires_macro.h"
#include "rapidschema/concepts/unique_types.h"
#include "rapidschema/meta/type_set.h"
#include "rapidschema/transform_result.h"

namespace rapidschema {
namespace internal {

template <typename Tuple, template <typename> typename Condition, size_t Index, class Enabled = void>
struct TupleElementWithCondition;

template <typename Tuple, template <typename> typename Condition, size_t I>
struct TupleElementWithCondition<
    Tuple,
    Condition,
    I,
    typename std::enable_if<Condition<typename std::tuple_element<I - 1, Tuple>::type>::value>::type> {
  using Type = typename std::tuple_element<I - 1, Tuple>::type;
  static constexpr size_t Index = I - 1;
};

template <typename Tuple, template <typename> typename Condition, size_t I>
struct TupleElementWithCondition<
    Tuple,
    Condition,
    I,
    typename std::enable_if<!Condition<typename std::tuple_element<I - 1, Tuple>::type>::value>::type> {
  using Type = typename TupleElementWithCondition<Tuple, Condition, I - 1>::Type;
  static constexpr size_t Index = TupleElementWithCondition<Tuple, Condition, I - 1>::Index;
};

template <typename Tuple, template <typename> class Condition>
struct TupleElementWithCondition<
    Tuple,
    Condition,
    0> {};

template <typename BaseClass, typename Tuple, size_t Index>
struct ConstTupleAccessor {
  static const BaseClass* Get(const Tuple& tuple, size_t index) {
    if (index == Index - 1) {
      return &std::get<Index - 1>(tuple);
    } else {
      return ConstTupleAccessor<BaseClass, Tuple, Index - 1>::Get(tuple, index);
    }
  }
};

template <typename BaseClass, typename Tuple>
struct ConstTupleAccessor<BaseClass, Tuple, 0> {
  static const BaseClass* Get(const Tuple& tuple, size_t index) {
    assert(false);
    return nullptr;
  }
};

template <typename BaseClass, typename Tuple, size_t Index>
struct TupleAccessor {
  static BaseClass* Get(Tuple* tuple, size_t index) {
    if (index == Index - 1) {
      return &std::get<Index - 1>(*tuple);
    } else {
      return TupleAccessor<BaseClass, Tuple, Index - 1>::Get(tuple, index);
    }
  }
};

template <typename BaseClass, typename Tuple>
struct TupleAccessor<BaseClass, Tuple, 0> {
  static BaseClass* Get(Tuple* tuple, size_t index) {
    assert(false);
    return nullptr;
  }
};

template <typename Tuple, typename Operation, size_t Index>
struct TupleApplyUntilSuccess {
  static size_t Apply(Operation&& operation, Tuple* tuple) {
    if (operation(std::get<Index - 1>(*tuple))) {
      return Index - 1;
    } else {
      return TupleApplyUntilSuccess<Tuple, Operation, Index - 1>::Apply(std::forward<Operation>(operation), tuple);
    }
  }
};

template <typename Tuple, typename Operation>
struct TupleApplyUntilSuccess<Tuple, Operation, 0> {
  static size_t Apply(Operation&& operation, Tuple* tuple) {
    return -1;
  }
};


template <typename Tuple, typename F, std::size_t ...Indices>
constexpr void ForEachImpl(Tuple&& tuple, F&& f, std::index_sequence<Indices...>) {
  using swallow = int[];
  (void)swallow{1,
                (f(std::get<Indices>(std::forward<Tuple>(tuple))), void(), int{})...
  };
}

template<typename T>
struct SameType {
  template<typename Y>
  using Condition = std::is_same<T, Y>;
};

template <typename... Ts> RAPIDSCHEMA_REQUIRES(UniqueTypes<Ts...>)
class UniqueTuple {
  static_assert(TypeSet<Ts...>::Unique(), "Types for unique tuple must be unique.");
  using TupleT = std::tuple<Ts...>;

 public:
  UniqueTuple() = default;

  explicit UniqueTuple(TupleT&& tuple)
      : tuple_(std::forward<TupleT>(tuple))
  {}

  template<template<typename> class Condition>
  using ElementWithCondition = TupleElementWithCondition<std::tuple<Ts...>, Condition, sizeof...(Ts)>;

  /// \brief retrieves the index of the tuple element for which the type meets the Condition
  /// if no element meets the condition there will be a compilation error.
  template <template<typename> class Condition>
  constexpr size_t IndexOf() {
    return ElementWithCondition<Condition>::Index;
  }

  /// \brief retrieves the (first from the back) tuple element for which the type meets the Condition
  /// if no element meets the condition there will be a compilation error.
  template <template<typename> class Condition>
  typename std::tuple_element<ElementWithCondition<Condition>::Index, TupleT>::type& GetIfCondition() {
    return std::get<ElementWithCondition<Condition>::Index>(tuple_);
  }

  /// \brief retrieves the (first from the back) tuple element for which the type meets the Condition
  /// if no element meets the condition there will be a compilation error.
  template <template<typename> class Condition>
  const typename std::tuple_element<ElementWithCondition<Condition>::Index, TupleT>::type& GetIfCondition() const {
    return std::get<ElementWithCondition<Condition>::Index>(tuple_);
  }

  /// \brief retrieves the tuple element with the given type T.
  template <typename T>
  const typename std::tuple_element<
      ElementWithCondition<SameType<T>::template Condition>::Index, TupleT>::type& GetType() const {
    return std::get<ElementWithCondition<SameType<T>::template Condition>::Index>(tuple_);
  }

  /// \brief retrieves the tuple element with the given type T.
  template <typename T>
  typename std::tuple_element<ElementWithCondition<SameType<T>::template Condition>::Index, TupleT>::type& GetType() {
    return std::get<ElementWithCondition<SameType<T>::template Condition>::Index>(tuple_);
  }

  template <typename BaseClass>
  const BaseClass* Get(size_t index) const {
    return ConstTupleAccessor<BaseClass, TupleT, sizeof...(Ts)>::Get(tuple_, index);
  }

  template <typename BaseClass>
  BaseClass* Get(size_t index) {
    return TupleAccessor<BaseClass, TupleT, sizeof...(Ts)>::Get(&tuple_, index);
  }

  template <typename Operation>
  int ApplyUntilSuccess(Operation&& operation) {
    return TupleApplyUntilSuccess<TupleT, Operation, sizeof...(Ts)>::Apply(std::forward<Operation>(operation), &tuple_);
  }

  template <typename Function>
  void ForEach(Function&& f) const {
    constexpr std::size_t N = std::tuple_size<std::remove_reference_t<TupleT>>::value;
    ForEachImpl(tuple_, std::forward<Function>(f), std::make_index_sequence<N>{});
  }

  size_t Size() const {
    return std::tuple_size<TupleT>::value;
  }

 private:
  TupleT tuple_;
};

}  // namespace internal
}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_META_UNIQUE_TUPLE_H_
