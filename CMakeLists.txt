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
        src/memory.h
        src/device.cpp
        src/device.h
        src/libraries/standard.h
        src/libraries/console.h
        src/program.h
        src/devices/console/console_device.cpp
        src/devices/console/console_device.h
        src/program.cpp)

# -------------------------------------
# Examples
# -------------------------------------

add_executable(
        fibonacci_example
        examples/fibonacci.cpp
        src/program.cpp
        src/program.h
        src/machine.cpp
        src/machine.h)

# -------------------------------------
# Unit tests
# -------------------------------------

include(CTest)
list(APPEND CMAKE_CTEST_ARGUMENTS "--output-on-failure")

if (BUILD_TESTING)
    add_executable(
            advance_test
            tests/advance.cpp
            src/machine.cpp
            src/machine.h
            tests/asserts.h)
    add_test(NAME advance_test COMMAND advance_test)

    add_executable(
            load_program_test
            tests/load_program.cpp
            src/program.cpp
            src/program.h
            tests/asserts.h)
    add_test(NAME load_program_test COMMAND load_program_test)

    add_executable(
            machine_test
            tests/machine.cpp
            src/machine.cpp
            src/machine.h
            tests/asserts.h)
    add_test(NAME machine_test COMMAND machine_test)
endif ()

# -------------------------------------
# Custom Targets
# -------------------------------------

# Runs clang-format and black on the code
add_custom_target(
        format
        COMMAND ./scripts/format.sh
        VERBATIM)

# Checks whether clang-format or black needs to be run and sets a non-zero exit
# code if so
add_custom_target(
        check-format
        COMMAND ./scripts/check-format.sh
        VERBATIM)

# Runs code generation for assembly libraries
add_custom_target(
        generate
        COMMAND ./scripts/generate.sh
        VERBATIM)
