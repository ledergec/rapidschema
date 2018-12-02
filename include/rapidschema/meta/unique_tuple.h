//
// Created by root on 11/28/18.
//

#ifndef INCLUDE_RAPIDSCHEMA_META_UNIQUE_TUPLE_H_
#define INCLUDE_RAPIDSCHEMA_META_UNIQUE_TUPLE_H_

#include <cassert>
#include <tuple>

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

template <typename Tuple, typename Visitor, size_t Index>
struct TupleVisitor {
  static TransformResult Visit(const Tuple& tuple, Visitor&& visitor, size_t index) {
    if (index == Index - 1) {
      return visitor(std::get<Index - 1>(tuple));
    } else {
      return TupleVisitor<Tuple, Visitor, Index - 1>::Visit(tuple, std::forward<Visitor>(visitor), index);
    }
  }
};

template <typename Tuple, typename Visitor>
struct TupleVisitor<Tuple, Visitor, 0> {
  static TransformResult Visit(const Tuple& tuple, Visitor&& visitor, size_t index) {
    assert(false);
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

template <typename... Ts>
class UniqueTuple {
  static_assert(TypeSet<Ts...>::Unique(), "Types for unique tuple must be unique.");
  using TupleT = std::tuple<Ts...>;

 public:
  UniqueTuple() = default;

  explicit UniqueTuple(Ts... ts)
      : tuple_(std::make_tuple(std::forward<Ts>(ts)...))
  {}

  template<template<typename> class Condition>
  using ElementWithCondition = TupleElementWithCondition<std::tuple<Ts...>, Condition, sizeof...(Ts)>;

  /// \brief retrieves the (first from the back) tuple element for which the type meets the Condition
  /// if no element meets the condition there will be a compilation error.
  template <template<typename> class Condition>
  typename std::tuple_element<ElementWithCondition<Condition>::Index, TupleT>::type& Get() {
    return std::get<ElementWithCondition<Condition>::Index>(tuple_);
  }

  /// \brief retrieves the (first from the back) tuple element for which the type meets the Condition
  /// if no element meets the condition there will be a compilation error.
  template <template<typename> class Condition>
  const typename std::tuple_element<ElementWithCondition<Condition>::Index, TupleT>::type& Get() const {
    return std::get<ElementWithCondition<Condition>::Index>(tuple_);
  }

  template <class Visitor>
  TransformResult Visit(Visitor &&visitor, size_t index) const {
    return TupleVisitor<TupleT, Visitor, sizeof...(Ts)>::Visit(tuple_, std::forward<Visitor>(visitor), index);
  }

  template <class Operation>
  int ApplyUntilSuccess(Operation&& operation) {
    return TupleApplyUntilSuccess<TupleT, Operation, sizeof...(Ts)>::Apply(std::forward<Operation>(operation), &tuple_);
  }

 private:
  TupleT tuple_;
};

}  // namespace internal
}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_META_UNIQUE_TUPLE_H_
