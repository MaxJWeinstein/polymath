#ifndef RESULT_H
#define RESULT_H

#include <string>

struct Result
{
    enum {INT, ERROR} tag;
    union
    {
        int wholeNum;
        std::string errorMsg;
    };

    Result(int num) : tag(INT), wholeNum(num) {};
    Result(std::string_view errMsg);
    Result(Result& other);
    Result(Result&& other);

    ~Result();
};
#endif // RESULT_H
