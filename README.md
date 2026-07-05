# Polymath

This project is meant to provide a suite of computational tools at the command
line. The primary goal of this suite of tools is to be fast and convenient to
use.

Some of the ideal functions are:

- Polynomial operations
    - Factoring
    - Root-finding
    - Multiplying
    - Dividing
    - Differentiation
- General numerical methods
    - Root-finding
    - Integration
    - (I don't find numerical differentiation that useful)
- Symbolic computation
    - Differentiation
- LaTeX generation

The real goal of this project is to get practice using C++, so it's very likely
that I won't finish all of these goals.

## Building

This project uses CMake. I'm just learning how to use it, so there may be issues.
I'm using `FetchContent` to include the `isocline` library. This makes the CLI
experience much nicer.

Also, just note that the backend is meant to be its own library that gets used
by the frontend.

## Specification/Design

I want to be able to open a terminal and write `math`, and be greeted with a
REPL-like program. Each line will either be an expression or definition.

A definition will either be a numerical variable or a polynomial (or eventually
even a general function). We'll say that a polynomial captures its context, so
using a variable as a coefficient causes the value of that variable to be
stored, with no relationship to the variable afterwards.

The expressions will include a lot of kinds, since expressions are composed of
expressions. The basic expressions are literals, variables, function evaluation,
basic math operations, and polynomial multiplication. The more complex
expressions are calls to the routines which are the purpose of this project.
Some routines don't have a value that makes sense to represent, and will return
a special value that throws an error if used.

It's best to just write examples.

```
# Defining a polynomial
math> poly f(x) = x^2 + 1

# Calling a function (general or polynomial)
math> f(1)
2

math> poly g(x) = x^2 + x

# Polynomial addition
math> f + g
2x^2 + x + 1

math> poly h(y) = y^3-1

# Only looking to support polynomials of one variable, so the fact that h was defined
# with a different independent variable doesn't matter
math> f + h
x^3 + x^2

# Polynomial multiplication
math> f*g
x^4 + x^3 + x^2 + x

# Differentiate polynomials. Note that h does "remember" that it was defined as h(y)
math> diff h
3y^2

# Higher-degree derivatives
math> diff{3} h
6

# Root-finding. Will have to be approximated in many cases
math> roots g
-1
0

# By default, consider complex roots
math> roots f
i
-i

# Factoring polynomials
math> factor g
x(x + 1)

# Default to factoring over R[x]
math> factor f
x^2 + 1

# Specify complex factorization
math> factor{C} f
(x - i)(x + i)

# Defining a general function. Some functions like sqrt, sin, exp, etc. will be builtins
math> func myFunc(x) = 1 + sqrt(x)

# Differentiating a general function
math> diff myFunc
1/(2*sqrt(x))

# Defining a constant. Constants like pi would be builtin.
# Would be cool to treat them symbolically where possible, so that pi/pi is exactly 1, not just 1.00
math> let pi = 3.14

# Declaring a symbolic variable. Domains would be cool, but not necessary
math> var t : R

# Defining a symbolic variable based on another symbolic variable
math> var A = sin(pi*t)

# Testing an evaluation over a symbolic variable
math> set t = 3/2
t = 3/2
A = -1

# Solve (basic) symbolic equations
math> solve{t} A = 1
t = 0.5
```

## Notes

I'm rethinking this project with heavy inspiration from a Cppcon23 talk on
symbolic computation.
