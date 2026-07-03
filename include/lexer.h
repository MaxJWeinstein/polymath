#ifndef LEXER_H
#define LEXER_H

#include <iostream>

struct Token {
    enum class Type {
        // ()=,:+-*/^{}
        // func let var diff roots factor solve
        // Integer Float Identifier
    };

    Token(Type t)
        : type { t }
    {
    }

    Type get_type() { return type; }

protected:
    Type type;
};

class TokenWithString : Token {
protected:
    TokenWithString(Type t, std::string str)
        : type { t }
        , str { str }
    {
    }
    ~TokenWithString { str.~basic_string(); }

public:
    std::string_view get_str() { return str; }

protected:
    std::string str;
};

class Lexer {
private:
    std::istream stream;
};

#endif // LEXER_H