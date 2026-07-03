/*
 * @file repl.cpp
 * @brief Read-Evaluate-Print-Loop for math-tools
 * @version 0.1
 * @date 2026-07-03
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "math_tools/repl.hpp"

#include <cstdlib>
#include <iostream>
#include <isocline.h>

#include "math_tools/core/evaluator.hpp"
#include "math_tools/core/lexer.hpp"
#include "math_tools/core/parser.hpp"

namespace math_tools {

namespace {
// Called on every keystroke
// Must tolerate partial input without throwing
void highlight(ic_highlight_env_t *henv, const char *input, void *) {
    auto tokens = core::lex(input); // MUST NOT THROW

    for (const auto &tok : tokens) {
        const char *style = nullptr;
        switch (tok.kind) {
        case core::TokenKind::Number:
            style = "ic-number";
            break;
        case core::TokenKind::Symbol:
            style = "ic-symbol";
            break;
        case core::TokenKind::Function:
            style = "ic-function";
            break;
        case core::TokenKind::Operator:
            style = "ic-operator";
            break;
        default:
            break;
        }
        if (style) {
            ic_highlight(henv, static_cast<long>(tok.startPos),
                         static_cast<long>(tok.length), style);
        }
    }
}

void setupIsocline() {
    ic_set_history(HISTORY_FILE.data(), -1);
    ic_enable_auto_tab(true);

    // Define colors for token categories
    ic_style_def("ic-number", "ansi-green");
    ic_style_def("ic-symbol", "ansi-cyan");
    ic_style_def("ic-function", "ansi-yellow bold");
    ic_style_def("ic-operator", "ansi-white");

    ic_set_default_highlighter(highlight, nullptr);
}
} // namespace

int runRepl() {
    setupIsocline();

    core::Evaluator evaluator;

    // TODO: use constant or macro for version number
    std::cout << "math-tools 0.1.0 - type an expression, or 'exit'\n";

    // REPL loop
    while (true) {
        char *input =
            ic_readline("math"); // isocline appends "> " to the prompt
        if (!input) {            // Received EOF
            break;
        }
        // Copy malloc-ed string over to std::string
        std::string line(input);
        free(input);

        // Handle special cases
        if (line == "exit" || line == "quit") {
            break;
        }
        if (line.empty()) {
            continue;
        }

        ic_history_add(line.c_str());

        try {
            auto tokens = core::lex(line);
            auto expr = core::parse(tokens);
            auto result = evaluator.evaluate(expr);
            std::cout << "  " << result->toString() << "\n";
        } catch (const std::exception &e) {
            std::cerr << "  error: " << e.what() << '\n';
        }
    }
    return 0;
}
} // namespace math_tools