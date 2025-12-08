#include <iostream>
#include <string>

#include "commandprocessor.h"
#include "result.h"

int main()
{
    std::string commands[] = {"5 + 4"};

    CommandProcessor commandProcessor{};

    for (auto command : commands) {
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
}
