#ifndef SYMBOLIC_H
#define SYMBOLIC_H

#include <type_traits>

// Type trait
template <class>
struct is_symbolic : std::false_type {};

// Variable template
template <class T>
inline constexpr bool is_symbolic_v = is_symbolic<T>::value;

// Concept
template <class T>
concept symbolic = is_symbolic_v<T>;

#endif