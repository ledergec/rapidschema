// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_COMBINED_CONSTRAINT_H_
#define INCLUDE_RAPIDSCHEMA_COMBINED_CONSTRAINT_H_

#include <rapidjson/document.h>

#include "rapidschema/concepts/correct_value_parameters.h"
#include "rapidschema/meta/unique_tuple.h"
#include "rapidschema/result.h"

namespace rapidschema {
namespace internal {

template <typename Tuple, typename T, size_t Index>
struct CheckAll {
  static Result Check(const Tuple& tuple, const T& t) {
    Result tmp;
    tmp.Append(std::get<Index - 1>(tuple).Check(t));
    tmp.Append(CheckAll<Tuple, T, Index - 1>::Check(tuple, t));
    return tmp;
  }
};

template <typename Tuple, typename T>
struct CheckAll<Tuple, T, 0> {
  static Result Check(const Tuple& tuple, const T& t) {
    return Result();
  }
};

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION
template <typename Tuple, typename SchemaType, size_t Index>
struct ConstraintToSchemaAdder {
  static void AddToSchema(const Tuple& tuple, std::shared_ptr<SchemaType> schema) {
    std::get<Index - 1>(tuple).AddToSchema(schema);
    ConstraintToSchemaAdder<Tuple, SchemaType, Index - 1>::AddToSchema(tuple, schema);
  }
};

template <typename Tuple, typename SchemaType>
struct ConstraintToSchemaAdder<Tuple, SchemaType, 0> {
  static void AddToSchema(const Tuple& tuple, std::shared_ptr<SchemaType> schema) {}
};
#endif

template<typename T, template<typename> class ... Constraints>
RAPIDSCHEMA_REQUIRES((CorrectValueParameters<T, Constraints...>))
class CombinedConstraint;

template<typename T, template<typename> class ... Constraints>
RAPIDSCHEMA_REQUIRES((CorrectValueParameters<T, Constraints...>))
static CombinedConstraint<T, Constraints...> MakeConstraint(Constraints<T>&&... constraints);

template<typename T, template<typename> class ... Constraints>
RAPIDSCHEMA_REQUIRES((CorrectValueParameters<T, Constraints...>))
class CombinedConstraint {
  using TupleT = internal::UniqueTuple<Constraints<T>...>;

 public:
  CombinedConstraint() = default;

  Result Check(const T& t) const {
    return CheckAll<typename TupleT::TupleT, T, TupleT::Size()>::Check(constraints_.GetTuple(), t);
  }

  template<template<typename> class Constraint>
  Constraint<T>& Get() {
    return constraints_.template GetType<Constraint<T>>();
  }

  template<template<typename> class Constraint>
  const Constraint<T>& Get() const {
    return constraints_.template GetType<Constraint<T>>();
  }

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION
  template <typename SchemaType>
  void AddToSchema(std::shared_ptr<SchemaType> schema) const {
    ConstraintToSchemaAdder<typename TupleT::TupleT, SchemaType, TupleT::Size()>::AddToSchema(
        constraints_.GetTuple(), schema);
  }
#endif

 private:
  explicit CombinedConstraint(TupleT&& constraints)
      : constraints_(std::forward<TupleT>(constraints)) {}

 private:
  TupleT constraints_;

  friend CombinedConstraint MakeConstraint<T, Constraints...>(Constraints<T>&&... constraints);
};

template<typename T, template<typename> class ... Constraints>
RAPIDSCHEMA_REQUIRES((CorrectValueParameters<T, Constraints...>))
static CombinedConstraint<T, Constraints...> MakeConstraint(Constraints<T>&&... constraints) {
  return CombinedConstraint<T, Constraints...>(internal::UniqueTuple<Constraints<T>...>(
      std::make_tuple(std::forward<Constraints<T>>(constraints)...)));
}

}  // namespace internal
}  // namespace rapidschema

#endif  // INCLUDE_RAPIDSCHEMA_COMBINED_CONSTRAINT_H_
