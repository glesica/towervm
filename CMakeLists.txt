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
            src/machine.cpp
            src/machine.h
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

file(GLOB MAIN_SOURCES
        "src/**.c"
        "src/**.cpp"
        "src/**.h"
        "src/**.hpp")
file(GLOB TEST_SOURCES
        "tests/**.c"
        "tests/**.cpp"
        "tests/**.h"
        "tests/**.hpp")
file(GLOB EXAMPLE_SOURCES
        "examples/**.c"
        "examples/**.cpp"
        "examples/**.h"
        "examples/**.hpp")

# Runs clang-format on the code
add_custom_target(
        format
        COMMAND clang-format -i ${MAIN_SOURCES} ${TEST_SOURCES}
        VERBATIM)

# Checks whether clang-format needs to be run and sets a non-zero
# exit code if so
add_custom_target(
        check-format
        COMMAND clang-format --dry-run --Werror ${MAIN_SOURCES} ${TEST_SOURCES}
        VERBATIM)

add_custom_target(
        generate-c
        COMMAND pipenv run python tools/generate.py libraries/standard.toml src/libraries/standard.h
        VERBATIM)

add_custom_target(
        generate-py
        COMMAND pipenv run python tools/generate.py libraries/standard.toml tools/towervm/libraries/standard.py
        VERBATIM)

add_custom_target(
        format-py
        COMMAND pipenv run black tools/
        VERBATIM)

add_custom_target(
        check-format-py
        COMMAND pipenv run black --check tools/
        VERBATIM)
