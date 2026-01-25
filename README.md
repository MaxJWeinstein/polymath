# Math Tools

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

I'm having some trouble getting the build system how I want it. Ideally, I'd
learn how to use CMake, since I think it will make sense for maintaining
project structure.

For now, `make` in the root creates object files in the `build` directory,
and the executable is in root, named `mathtools`.

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
$> func myFunc(x) = 1 + sqrt(x)
myFunc(x) = 1 + sqrt(x)

$> let pi = 3.14
pi = 3.14

$> var t : R

$> let A = sin(t/pi)

$> poly f(x) = x^2 + 1
f(x) = x^2 + 1

$> f(1)
2

$> poly g(x) = x^2 + x
g(x) = x^2 + x

$> f + g
2x^2 + x + 1

$> poly h(y) = y^3-1
h(y) = y^3 - 1

$> f + h
x^3 + x^2

$> f*g
x^4 + x^3 + x^2 + x

$> diff h
3y^2

$> diff{3} h
6

$> roots g
-1
0

$> roots f
i
-i

$> factor g
x(x + 1)

$> factor f
x^2 + 1

$> factor{C} f
(x - i)(x + i)
```

## Notes

I'm rethinking this project with heavy inspiration from a Cppcon23 talk on
symbolic computation.
