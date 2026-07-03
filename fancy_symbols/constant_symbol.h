#ifndef CONSTANT_SYMBOL_H
#define CONSTANT_SYMBOL_H

#include "substitution.h"
#include "symbolic.h"

template <auto Value>
struct constant_symbol {
    using type = decltype(Value);
    static constexpr type value = Value;

    template <class... Binders>
    constexpr auto operator()(const substitution<Binders...>& s) const {
        return value;
    }
}

template <auto Value>
struct is_symbolic<constant_symbol<Value>> : std::true_type {
};

#endif