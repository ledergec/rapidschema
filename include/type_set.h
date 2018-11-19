//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef RAPIDJSON_TYPE_SET_H
#define RAPIDJSON_TYPE_SET_H

#include "to_json_type.h"

namespace rapidoson {

    template <typename... Ss>
    struct TypeSet {
    public:
        template <typename T>
        static constexpr bool Contains();

        static constexpr bool Unique();
    };

    template <typename S, typename... Ss>
    struct TypeSet<S, Ss...> {
    public:
        template <typename T>
        static constexpr bool Contains() {
            return ToJsonType<T>::value == ToJsonType<S>::value || TypeSet<Ss...>::template Contains<T>();
        }

        static constexpr bool Unique() {
            return !TypeSet<Ss...>::template Contains<S>() && TypeSet<Ss...>::Unique();
        }
    };

    template <>
    struct TypeSet<> {
    public:
        template <typename T>
        static constexpr bool Contains() {
            return false;
        }

        static constexpr bool Unique() {
            return true;
        }
    };

}  // rapidjson

#endif //RAPIDJSON_TYPE_SET_H
