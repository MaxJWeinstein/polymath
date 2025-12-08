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
    Result(std::string_view errMsg) : tag(ERROR)
    {
        this->errorMsg = std::string(errMsg);
    }

    Result(Result& other) : tag(other.tag)
    {
        switch (other.tag) {
            case ERROR:
                this->errorMsg = other.errorMsg;
                break;
            case INT:
                this->wholeNum = other.wholeNum;
                break;
        }
    }

    Result(Result&& other) : tag(other.tag)
    {
        switch (other.tag) {
            case ERROR:
                this->errorMsg = std::move(other.errorMsg);
                break;
            case INT:
                this->wholeNum = other.wholeNum;
                break;
        }
    }

    ~Result()
    {
        switch (this->tag) {
            case ERROR:
                this->errorMsg.~basic_string();
                break;
            default:
                return;
        }
    }
};
#endif // RESULT_H
