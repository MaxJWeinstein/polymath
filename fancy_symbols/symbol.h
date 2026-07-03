// Strongly inspired by Vincent Reverdy's tutorial from Cppcon23
#ifndef SYMBOL_H
#define SYMBOL_H

#include <utility>

#include "substitution.h"
#include "symbol_binder.h"
#include "symbol_constraints.h"

template <class>
struct symbol_id {
    static constexpr auto singleton = [] {};  // type/value doesn't matter
    static constexpr const void* address = std::addressof(singleton);
};

// Each instantiated symbol is a unique type
template <class Trait = unconstrained, auto Id = symbol_id<decltype([] {})>{}>
struct symbol {
    static constexpr auto id = Id;

    template <class Arg>
        requires Trait::template
    trait<std::remove_cvref_t<Arg>>::value constexpr symbol_binder<symbol,
                                                                   Arg&&>
    operator=(Arg&& arg) const {
        return symbol_binder(*this, std::forward<Arg>(arg));
    }

    template <class... Binders>
    constexpr auto operator()(const substitution<Binders...>& s) const {
        return s[id]();
    }
};

template <class Lhs, class Rhs>
constexpr std::strong_ordering operator<=>(symbol_id<Lhs>, symbol_id<Rhs>) {
    return std::compare_three_way{}(symbol_id<Lhs>::address,
                                    symbol_id<Rhs>::address);
}

template <class T, auto Id>
struct is_symbolic<symbol<T, Id>> : std::true_type {};

#endif