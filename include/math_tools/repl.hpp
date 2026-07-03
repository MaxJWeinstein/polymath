#pragma once

#include <string_view>

namespace math_tools {
constexpr std::string_view HISTORY_FILE = ".math_tools_history";
int runRepl();
} // namespace math_tools