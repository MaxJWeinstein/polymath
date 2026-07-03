add_library(math_tools_core STATIC
    src/lexer.cpp
    src/parser.cpp
    src/expr.cpp
    src/evaluator.cpp
)

target_include_directories(math_tools_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(math_tools_core PUBLIC cxx_std_20)