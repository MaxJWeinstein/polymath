#ifndef SUBSTITUTION_H
#define SUBSTITUTION_H

#include <cstddef>
#include <type_traits>
#include <utility>

// A pack of binders indexed by identifier

// Type of index constant
template <std::size_t I>
struct index_constant : std::integral_constant<std::size_t, I> {};

template <std::size_t I>
inline constexpr index_constant<I> index_v = {};

template <std::size_t I, class Binder>
struct substitution_element;

template <class Sequence, class... Binders>
struct substitution_base;

// Substitution wrapper class
template <class... Binders>
struct substitution
    : substitution_base<std::index_sequence_for<Binders...>, Binders...> {
    using base =
        substitution_base<std::index_sequence_for<Binders...>, Binders...>;
    using base::base;
    using base::operator[];
};
// Deduction guide
template <class... Binders>
substitution(const Binders&...) -> substitution<Binders...>;

// Substitution base
template <std::size_t... Index, class... Binders>
struct substitution_base<std::index_sequence<Index...>, Binders...>
    : substitution_element<Index, Binders>... {
    using index_sequence = std::index_sequence<Index...>;
    using substitution_element<Index, Binders>::operator[]...;
    constexpr substitution_base(const Binders&... x)
        : substitution_element<Index, Binders>(x)... {}
};

// Substitution element
template <std::size_t I, class Binder>
struct substitution_element {
    using index = index_constant<I>;
    using id_type = decltype(Binder::symbol_type::id);
    // Constructor
    constexpr substitution_element(const Binder& b) : _binder(b) {}
    // Access by index
    constexpr const Binder& operator[](index) const { return _binder; }
    // Access by id
    constexpr const Binder& operator[](id_type) const { return _binder; }

   private:
    const Binder _binder;
};

#endif