#include "polymath/core/lexer.hpp"

#include <cctype>

namespace polymath::core
{

    namespace
    {

        bool isIdentStart(char c)
        {
            return std::isalpha(static_cast<unsigned char>(c)) || c == '_';
        }

        bool isIdentChar(char c)
        {
            return std::isalnum(static_cast<unsigned char>(c)) || c == '_';
        }

    } // namespace

    std::vector<Token> lex(const std::string &input) noexcept
    {
        std::vector<Token> tokens;
        const std::size_t N = input.size();
        std::size_t i = 0;

        while (i < N)
        {
            char c = input[i];

            // Skip whitespace
            if (std::isspace(static_cast<unsigned char>(c)))
            {
                i++;
                continue;
            }

            std::size_t start = i;

            // --- Numbers ---
            if (std::isdigit(static_cast<unsigned char>(c)))
            {
                bool seenDot = false; // Stop before the second '.' in '3.4.5'
                while (i < N && (std::isdigit(static_cast<unsigned char>(input[i])) || (input[i] == '_') || (input[i] == '.' && !seenDot)))
                {
                    if (input[i] == '.')
                    {
                        seenDot = true;
                    }
                    i++;
                }
                tokens.push_back({TokenKind::Number, start, i - start, input.substr(start, i - start)});
                continue;
            }

            // --- Identifiers ---
            // Just note that separating functions and symbols here will allow you to differentiate function calls from implicit multiplication
            if (isIdentStart(c))
            {
                while (i < N && isIdentChar(input[i]))
                {
                    i++;
                }
                std::string text = input.substr(start, i - start);
                // Peek ahead one character for left paren
                TokenKind kind = (i < N && input[i] == '(') ? TokenKind::Function : TokenKind::Symbol;
                tokens.push_back({kind, start, i - start, text});
                continue;
            }

            // --- Two-character operators ---
            if ((c == '(') && (i + 1 < N) && (input[i + 1] == '='))
            {
                tokens.push_back({TokenKind::Operator, start, 2, input.substr(start, 2)});
                i += 2;
                continue;
            }

            // --- Single-character operators ---
            bool isOp = false;
            switch (c)
            {
            case '+':
            case '-':
            case '*':
            case '/':
            case '^':
            case '=':
                isOp = true;
            }
            if (isOp)
            {
                tokens.push_back({TokenKind::Operator, start, 1, std::string(1, c)});
                i++;
                continue;
            }

            // --- Structural tokens ---
            if (c == '(')
            {
                tokens.push_back({TokenKind::LParen, start, 1, "("});
                i++;
                continue;
            }
            if (c == ')')
            {
                tokens.push_back({TokenKind::RParen, start, 1, ")"});
                i++;
                continue;
            }
            if (c == ',')
            {
                tokens.push_back({TokenKind::Comma, start, 1, ","});
                i++;
                continue;
            }

            // --- Unknown ---
            tokens.push_back({TokenKind::Unknown, start, 1, std::string(1, c)});
            i++;
        }

        return tokens;
    }

    const char *tokenKindToStr(TokenKind kind)
    {
        switch (kind)
        {
        case TokenKind::Comma:
            return "Comma";
        case TokenKind::End:
            return "End";
        case TokenKind::Function:
            return "Function";
        case TokenKind::LParen:
            return "LParen";
        case TokenKind::Number:
            return "Number";
        case TokenKind::Operator:
            return "Operator";
        case TokenKind::RParen:
            return "RParen";
        case TokenKind::Symbol:
            return "Symbol";
        case TokenKind::Unknown:
            return "Unknown";
        default:
            return "<Invalid TokenKind>";
        }
    }
} // namespace polymath::core
