#pragma once

#include <string_view>

namespace polymath
{
    constexpr std::string_view HISTORY_FILE = ".polymath_history";
    int runRepl();
} // namespace polymath