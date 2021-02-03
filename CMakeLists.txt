cmake_minimum_required(VERSION 3.17)
project(
        towervm
        VERSION 0.1.0
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY build)

# -------------------------------------
# Programs
# -------------------------------------

# The VM itself
add_executable(
    towervm
    src/towervm.cpp
    src/machine.cpp
    src/machine.h
    src/errors.cpp
    src/errors.h
    src/opcodes.h
    src/memory.h
    src/device.cpp
    src/device.h
)

# Assembler
add_executable(
    towervm_asm
    src/towervm_asm.cpp
    src/parser.cpp
    src/parser.h
    src/assembler.cpp
    src/assembler.h
)

# REPL
add_executable(
    towervm_repl
    src/towervm_repl.cpp
    src/parser.cpp
    src/parser.h
    src/assembler.cpp
    src/assembler.h
)

# -------------------------------------
# Examples
# -------------------------------------

add_executable(
    fibonacci_example
    examples/fibonacci.cpp
    src/machine.cpp
    src/machine.h
    src/errors.cpp
    src/errors.h
    src/opcodes.h
)

# -------------------------------------
# Unit tests
# -------------------------------------

include(CTest)
list(APPEND CMAKE_CTEST_ARGUMENTS "--output-on-failure")

if(BUILD_TESTING)
    add_executable(
        execute_test
        tests/execute.cpp
        src/machine.cpp
        src/machine.h
        src/opcodes.h
        tests/asserts.h
    )
    add_test(NAME execute_test COMMAND execute_test)

    add_executable(
        load_program_test
        tests/load_program.cpp
        src/machine.cpp
        src/machine.h
        tests/asserts.h
    )
    add_test(NAME load_program_test COMMAND load_program_test)

    add_executable(
        machine_test
        tests/machine.cpp
        src/machine.cpp
        src/machine.h
        tests/asserts.h
    )
    add_test(NAME machine_test COMMAND machine_test)

    add_executable(
        parser_test
        tests/parser.cpp
        src/parser.cpp
        src/parser.h
        tests/asserts.h
    )
    add_test(NAME parser_test COMMAND parser_test)
endif()

# -------------------------------------
# Custom Targets
# -------------------------------------

file(GLOB MAIN_SOURCES
    "src/**.c"
    "src/**.cpp"
    "src/**.h"
    "src/**.hpp"
)
file(GLOB TEST_SOURCES
    "tests/**.c"
    "tests/**.cpp"
    "tests/**.h"
    "tests/**.hpp"
)
file(GLOB EXAMPLE_SOURCES
    "examples/**.c"
    "examples/**.cpp"
    "examples/**.h"
    "examples/**.hpp"
)

# Runs clang-format on the code
add_custom_target(
        format
        COMMAND clang-format -i ${MAIN_SOURCES} ${TEST_SOURCES} ${EXAMPLE_SOURCES}
        VERBATIM
)

# Checks whether clang-format needs to be run and sets a non-zero
# exit code if so
add_custom_target(
        check-format
        COMMAND clang-format --dry-run --Werror ${MAIN_SOURCES} ${TEST_SOURCES} ${EXAMPLE_SOURCES}
        VERBATIM
)
