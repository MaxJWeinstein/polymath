#ifndef FORMULA_H
#define FORMULA_H

#include "substitution.h"
#include "symbolic.h"

template <symbolic Expression>
struct formula {
    using expression = Expression;

    // Constructor
    constexpr formula(Expression expr) noexcept {};
    // Call operator (substitution)
    template <class... Args>
    constexpr auto operator()(Args... args) const noexcept {
        return expression{}(substitution(args...));
    }
};

#endif