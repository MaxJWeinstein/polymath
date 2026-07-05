/*
 * @file lexer.hpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-07-03
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

namespace math_tools::core
{

    enum class TokenKind
    {
        Number,   // Number literal
        Symbol,   // Identifier not followed by a (
        Function, // Identifier followed by a (
        Operator, // Only recognized operators
        LParen,   //
        RParen,   //
        Comma,    //
        Unknown,  //
        End       // Sentinel to mark end of input
    };

    const char *tokenKindToStr(TokenKind kind);

    struct Token
    {
        TokenKind kind;
        std::size_t startPos;
        std::size_t length;
        std::string text;
    };

    std::vector<Token> lex(const std::string &input) noexcept;

} // namespace math_tools::core

using namespace math_tools::core;
static std::ostream &operator<<(std::ostream &os, const Token &token)
{
    const char *kind = tokenKindToStr(token.kind);
    return os << "Token(kind=" << kind << ", text='" << token.text << "')";
}

template <typename T>
std::ostream &operator<<(std::ostream &os, std::vector<T> vect)
{
    os << '[';
    for (size_t i = 0; i < vect.size(); i++)
    {
        if (i > 0)
        {
            os << ", ";
        }
        os << vect[i];
    }
    os << ']';
    return os;
}