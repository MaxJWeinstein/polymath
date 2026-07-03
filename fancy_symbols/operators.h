#ifndef OPERATORS_H
#define OPERATORS_H

#include <functional>

#include "expression.h"
#include "symbolic.h"

template <symbolic Lhs, symbolic Rhs>
constexpr symbolic_expression<std::plus<void>, Lhs, Rhs> operator+(
    Lhs, Rhs) noexcept {
    return {};
}

template <symbolic Lhs, symbolic Rhs>
constexpr symbolic_expression<std::minus<void>, Lhs, Rhs> operator-(
    Lhs, Rhs) noexcept {
    return {};
}

template <symbolic Lhs, symbolic Rhs>
constexpr symbolic_expression<std::multiplies<void>, Lhs, Rhs> operator*(
    Lhs, Rhs) noexcept {
    return {};
}

template <symbolic Lhs, symbolic Rhs>
constexpr symbolic_expression<std::divides<void>, Lhs, Rhs> operator/(
    Lhs, Rhs) noexcept {
    return {};
}

#endif