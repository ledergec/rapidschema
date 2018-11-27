//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef RAPIDJSON_JSON_TYPE_SET_H
#define RAPIDJSON_JSON_TYPE_SET_H

#include "type_properties.h"

namespace rapidoson {

    template <typename... Ss>
    struct JsonTypeSet {
    public:
        template <typename T>
        static constexpr bool Contains();

        static constexpr bool Unique();
    };

    template <typename S, typename... Ss>
    struct JsonTypeSet<S, Ss...> {
    public:
        template <typename T>
        static constexpr bool Contains() {
            return TypeProperties<T>::json_type == TypeProperties<S>::json_type ||
                    JsonTypeSet<Ss...>::template Contains<T>();
        }

        static constexpr bool Unique() {
            return !JsonTypeSet<Ss...>::template Contains<S>() && JsonTypeSet<Ss...>::Unique();
        }
    };

    template <>
    struct JsonTypeSet<> {
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

#endif //RAPIDJSON_JSON_TYPE_SET_H
