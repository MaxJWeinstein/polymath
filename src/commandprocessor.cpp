#include <iostream>
#include <stdexcept>
#include <string>
#include <regex>

#include "commandprocessor.h"

Result CommandProcessor::processCommand(std::string command)
{
    if (this->debug) {
        std::cout << "command: " << command << std::endl;
    }
    std::string addition_pattern = "([0-9]+)\\s*\\+\\s*([0-9]+)";
    std::regex addition_regex(addition_pattern);
    std::smatch command_match;
    if (std::regex_search(command, command_match, addition_regex)) {
        const std::string lhsStr = command_match[1];
        const std::string rhsStr = command_match[2];
        std::size_t posL{};
        std::size_t posR{};
        try
        {
            const int lhs {std::stoi(lhsStr, &posL)};
            const int rhs {std::stoi(rhsStr, &posR)};
            return Result{lhs + rhs};
        }
        catch (std::invalid_argument const& ex)
        {
            return Result{ex.what()};
        }
        catch (std::out_of_range const& ex)
        {
            return Result{ex.what()};
        }
    }
    return Result{"Unknown command: '" + command + "'"};
}
