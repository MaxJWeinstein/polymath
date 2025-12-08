#ifndef NUMBER_H
#define NUMBER_H

#include <optional>
#include <string_view>

class Number
{
public:
    enum Type {
        INT,
        FLOAT
    } type;

    union {
        int integer;
        float real;
    };

    Number(int i) : type(INT), integer(i) {}
    Number(float f) : type(FLOAT), real(f) {}

    static std::optional<Number> strToNum(std::string_view str);
};

#endif // NUMBER_H
