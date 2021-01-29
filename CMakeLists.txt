cmake_minimum_required(VERSION 3.17)
project(towervm)

set(CMAKE_CXX_STANDARD 20)

# -------------------------------------
# Programs
# -------------------------------------

# The VM itself
add_executable(towervm towervm.cpp machine.cpp machine.h opcodes.h errors.h registers.h memory.h)

# Assembler
add_executable(towervm_asm towervm_asm.cpp parser.cpp parser.h)

# -------------------------------------
# Unit tests
# -------------------------------------

enable_testing()
list(APPEND CMAKE_CTEST_ARGUMENTS "--output-on-failure")

add_executable(execute_test tests/execute.cpp machine.cpp machine.h opcodes.h errors.h registers.h tests/asserts.h)
add_test(NAME execute_test COMMAND execute_test)

add_executable(load_program_test tests/load_program.cpp machine.cpp machine.h)
add_test(NAME load_program_test COMMAND load_program_test)

add_executable(machine_test tests/machine.cpp machine.cpp machine.h)
add_test(NAME machine_test COMMAND machine_test)

# -------------------------------------
# Custom Targets
# -------------------------------------

file(GLOB SOURCES "./**.c" "./**.cpp" "./**.h" "./**.hpp")

# Runs clang-format on the code
add_custom_target(
        format
        COMMAND clang-format -i ${SOURCES}
        VERBATIM
)

# Checks whether clang-format needs to be run and sets a non-zero
# exit code if so
add_custom_target(
        check-format
        COMMAND clang-format --dry-run --Werror ${SOURCES}
        VERBATIM
)
