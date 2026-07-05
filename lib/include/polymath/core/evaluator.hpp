/*
 * @file evaluator.hpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-07-03
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include <vector>

#include "polymath/core/lexer.hpp"

namespace polymath::core
{
    class Evaluator
    {
    public:
        std::vector<Token> evaluate(std::vector<Token> tokens) { return tokens; }
    };
}