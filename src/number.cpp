#include <optional>
#include <regex>
#include <stdexcept>
#include <string_view>
#include <string>

#include "number.h"

std::optional<Number> Number::strToNum(std::string_view str) {
    std::string int_pat = "([\\-\\+]?)([0-9]+)";
    std::regex int_regex(int_pat);
    std::smatch match;
    if (std::regex_match(str.cbegin(), str.cend(), match, int_regex)) {
        const std::string numStr = match[0].str();
        try
        {
            const int val = std::stoi(numStr);
            return std::optional(Number(val));
        }
        catch (std::invalid_argument const& ex)
        {
            return {};
        }
        catch (std::out_of_range const& ex)
        {
            return {};
        };
    }
    else {
        return {};
    }
}
