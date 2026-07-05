/*
 * @file expr.hpp
 * @brief Symbolic expression tree
 * @version 0.1
 * @date 2026-07-03
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once
#include <memory>
#include <string>
#include <vector>

namespace polymath::core
{
  enum class ExprKind
  {
    Number,
    Symbol,
    Add,
    Mul,
    Pow,
    Function
  };

  class Expr;
  using ExprPtr = std::shared_ptr<const Expr>;

  class Expr
  {
  public:
    ExprKind kind;
    double value = 0.0;
    std::string name;
    std::vector<ExprPtr> args;

    std::string toString() const;
  };

  // Factories
  ExprPtr makeNumber(double v);
  ExprPtr makeSymbol(std::string name);
  ExprPtr makeAdd(ExprPtr a, ExprPtr b);
  ExprPtr makeMul(ExprPtr a, ExprPtr b);
  ExprPtr makePow(ExprPtr base, ExprPtr exp);
  ExprPtr makeFunction(std::string name, std::vector<ExprPtr> args);

} // namespace polymath::core