#include <string>

#include "result.h"

Result::Result(std::string_view errMsg) : tag(ERROR)
{
    this->errorMsg = std::string(errMsg);
}

Result::Result(Result& other) : tag(other.tag)
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

Result::Result(Result&& other) : tag(other.tag)
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

Result::~Result()
{
    switch (this->tag) {
        case ERROR:
            this->errorMsg.~basic_string();
            break;
        default:
            return;
    }
}
