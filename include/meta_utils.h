//
// Created by root on 11/28/18.
//

#ifndef RAPIDOSON_META_HELPER_H
#define RAPIDOSON_META_HELPER_H

#include <iostream>
#include <optional>
#include <string>
#include <type_traits>

#include <rapidjson/document.h>

#include "transform_result.h"

namespace rapidoson {

    namespace internal {

        template<typename T, typename Tuple, std::size_t I = 0, class Enabled = void>
        struct TupleAccessor {
            static T& Get(Tuple& tuple) {
                return std::get<I + 1>(tuple);
            }
        };

        template<typename T, typename Tuple, std::size_t I>
        struct TupleAccessor<T, Tuple, I, typename std::enable_if<std::is_same<T, typename std::tuple_element<I, Tuple>::type>::value>::type> {
            static T& Get(Tuple& tuple) {
                return std::get<I>(tuple);
            }
        };

        template<typename T, typename Tuple, std::size_t I>
        struct TupleAccessor<T, Tuple, I, typename std::enable_if<I == std::tuple_size<Tuple>::value>::type> {
        };

        template <typename Tuple, typename F, std::size_t ...Indices>
        constexpr void ForEachImpl(Tuple&& tuple, F&& f, std::index_sequence<Indices...>) {
            using swallow = int[];
            (void)swallow{1,
                          (f(std::get<Indices>(std::forward<Tuple>(tuple))), void(), int{})...
            };
        }

        template <typename Tuple, typename F>
        void ForEach(Tuple &&tuple, F &&f) {
            constexpr std::size_t N = std::tuple_size<std::remove_reference_t<Tuple>>::value;
            ForEachImpl(std::forward<Tuple>(tuple), std::forward<F>(f),
                          std::make_index_sequence<N>{});
        }

    }  // namespace internal


}  // namespace rapidoson

#endif //RAPIDOSON_META_HELPER_H
