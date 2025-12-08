#include <iostream>
#include <string>

#include "commandprocessor.h"
#include "result.h"

int main()
{
    std::cout << "Currently just a calculator" << std::endl;

    std::string command = "5 + 4";
    std::cout << "command: " << command << std::endl;

    CommandProcessor commandProcessor{};

    Result result = commandProcessor.processCommand(command);

    switch (result.tag) {
        case Result::INT:
            std::cout << "result: " << result.wholeNum << std::endl;
            break;
        case Result::ERROR:
            std::cout << "error encountered: " << result.errorMsg << std::endl;
            break;
    }
}
