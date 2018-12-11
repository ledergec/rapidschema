//
// Created by root on 12/10/18.
//

#ifndef INCLUDE_RAPIDSCHEMA_CONCEPTS_CORRECT_VALUE_PARAMETERS_H_
#define INCLUDE_RAPIDSCHEMA_CONCEPTS_CORRECT_VALUE_PARAMETERS_H_

#ifdef RAPIDSCHEMA_WITH_CONCEPTS

#include "rapidschema/concepts/constraint.h"
#include "rapidschema/concepts/has_type_properties.h"
#include "rapidschema/concepts/unique_types.h"

namespace rapidschema {

/// \brief Concept checking whether:
/// - the template parameter set defines a set of constraints
/// - HasPorperties<T> has been implemented
/// - all the constraints are unique
template<typename T, template<typename> class ... Constraints>
concept bool CorrectValueParameters = AreConstraints<T, Constraints...> &&
                                      HasTypeProperties<T> &&
                                      UniqueTypes<Constraints<T>...>;

}  // namespace rapidschema

#endif

#endif  // INCLUDE_RAPIDSCHEMA_CONCEPTS_CORRECT_VALUE_PARAMETERS_H_

