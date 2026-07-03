#ifndef SYMBOL_CONSTRAINTS_H
#define SYMBOL_CONSTRAINTS_H

#include <type_traits>

// Also inspired by the Cppcon23 talk
// Allows us to specify symbol<real>, for example
// A bit hacky wrapping traits in types, because you can't put concepts in
// templates

struct unconstrained {
    template <class Arg>
    struct trait : std::true_type {};
};

struct real {
    template <class Arg>
    struct trait : std::is_floating_point<Arg> {};
};

#endif