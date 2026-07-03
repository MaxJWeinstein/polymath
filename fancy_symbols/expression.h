#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "substitution.h"
#include "symbolic.h"

template <class Operator, symbolic... Terms>
struct symbolic_expression {
    template <class... Binders>
    constexpr auto operator()(
        const substitution<Binders...>& s) const noexcept {
        return Operator{}(Terms{}(s)...);
    }
};

template <class Operator, symbolic... Terms>
struct is_symbolic<symbolic_expression<Operator, Terms...>> : std::true_type {};

#endif