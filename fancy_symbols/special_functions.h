#ifndef SPECIAL_FUNCTIONS_H
#define SPECIAL_FUNCTIONS_H

#include <cmath>

#include "expression.h"
#include "symbolic.h"

// Function object
struct sin_symbol {
    template <class Arg>
    constexpr auto operator()(Arg&& arg) {
        return std::sin(std::forward<Arg>(arg));
    }
};

// Function builder
template <symbolic Arg>
constexpr symbolic_expression<sin_symbol, Arg> sin(Arg) noexcept {
    return {};
}

#endif