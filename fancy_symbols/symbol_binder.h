// Strongly inspired by Vincent Reverdy's tutorial from Cppcon23
#ifndef SYMBOL_BINDER_H
#define SYMBOL_BINDER_H

#include <type_traits>
#include <utility>
// We want to store an lvalue reference (T&) as a const lvalue reference (const
// T&) But if given an rvalue reference (T&&), we want to store the data (const
// T)

// lvalues

template <class T>
struct remove_lvalue_reference : std::type_identity<T> {};

template <class T>
    requires std::is_lvalue_reference_v<T>
struct remove_lvalue_reference<T>
    : std::type_identity<std::remove_reference_t<T>> {};

template <class T>
using remove_lvalue_reference_t = remove_lvalue_reference<T>::type;

// rvalues

template <class T>
struct remove_rvalue_reference : std::type_identity<T> {};

template <class T>
    requires std::is_rvalue_reference_v<T>
struct remove_rvalue_reference<T>
    : std::type_identity<std::remove_reference_t<T>> {};

template <class T>
using remove_rvalue_reference_t = remove_rvalue_reference<T>::type;

// properly insert const into reference types
template <class T>
struct requalify_as_const
    : std::conditional<
          std::is_lvalue_reference_v<T>,
          std::add_lvalue_reference_t<
              std::add_const_t<std::remove_reference_t<T>>>,
          std::conditional_t<std::is_rvalue_reference_v<T>,
                             std::add_rvalue_reference_t<
                                 std::add_const_t<std::remove_reference_t<T>>>,
                             std::add_const_t<T>>> {};
template <class T>
using requalify_as_const_t = requalify_as_const<T>::type;

template <class Symbol, class T>
struct symbol_binder {
    using symbol_type = Symbol;
    using value_type = std::remove_cvref_t<T>;
    static constexpr Symbol symbol = {};
    // Constructors
    template <class U>
        requires std::is_convertible_v<
            U&&, requalify_as_const_t<remove_rvalue_reference_t<T>>>
    constexpr symbol_binder(Symbol, U&& x) noexcept(
        std::is_nothrow_convertible_v<
            U&&, requalify_as_const_t<remove_rvalue_reference_t<T>>>)
        : value(std::forward<U>(x)) {}
    // Accessors
    const value_type& operator()() const noexcept { return value; }

   private:
    requalify_as_const_t<remove_rvalue_reference_t<T>> value;
};
// Deduction guide
template <class Symbol, class T>
symbol_binder(Symbol, T&&) -> symbol_binder<Symbol, T&&>;

#endif