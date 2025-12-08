#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>
#include <vector>

#include "number.h"

template<typename V>
class Expression
{
public:
    V val;
    std::string representation;
    std::vector<Expression> subExpressions;

    virtual V evaluate();

    virtual Expression<V> simplify();

    Expression(V val) : val(val) {}
};

class NumberExpression : Expression<Number>
{
    NumberExpression(Number v) : Expression(v) {}
};

class AddExpression : Expression<Number>
{
    Number evaluate() override;
    
};

#endif // EXPRESSION_H
