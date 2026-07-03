#include "math_tools/core/lexer.hpp"

#include <cctype>

namespace math_tools::core
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
            // Just not that separating functions and symbols here will allow you to differentiate function calls from implicit multiplication

            // --- Two-character operators ---

            // --- Single-character operators ---

            // --- Structural tokens ---

            // --- Unknown ---
            tokens.push_back({TokenKind::Unknown, start, 1, std::string(1, c)});
            i++;
        }

        return tokens;
    }
} // namespace math_tools::core
