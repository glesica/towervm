// Machine state

#ifndef TOWERVM_MACHINE_H
#define TOWERVM_MACHINE_H

#include <array>
#include <cstdint>
#include <cstdlib>

#include "errors.h"
#include "memory.h"

#define TARGET_MACHINE_SIZE 2048
#define TARGET_REG_COUNT 8
#define TARGET_MEM_COUNT (TARGET_MACHINE_SIZE - TARGET_REG_COUNT - 1)

typedef struct {
  // General purpose registers.
  mem_value reg[TARGET_REG_COUNT];

  // Program counter holds the address in memory of the
  // next instruction to be executed.
  uint32_t pc;

  // Main memory where the program and data are stored.
  mem_value mem[TARGET_MEM_COUNT];
} machine;

/**
 * Expands to the size of the machine's physical memory in
 * addressable words.
 */
#define MEM_SIZE(M) (sizeof((M)->mem) / sizeof((M)->mem[0]))

/**
 * Expands to the number of general purpose registers available on
 * the given instance of the machine.
 */
#define REG_COUNT(M) (sizeof((M)->reg) / sizeof((M)->reg[0]))

/**
 * Read and store a value from memory based on the current location
 * of the program counter, then increment the counter to be ready
 * for the next read. This pattern allows us to implement jumps by
 * simply modifying the program counter itself.
 */
#define READ_PC(M, A)                                                          \
  mem_value A = M->mem[M->pc];                                                 \
  M->pc += 1;

/**
 * Move the program forward by executing one instruction and
 * leaving the machine in a consistent state, ready for the next. If
 * an error occurred during execution, it is reflected in the returned
 * struct.
 */
machine_error execute(machine *m);

/**
 * Reset the machine state to be ready to run a new program and then
 * read the program, as an array of opcodes and data, into the machine.
 * After this function returns the machine is ready to have `execute`
 * called on it.
 */
void load_program(machine *m, const mem_value values[], uint64_t value_count);

#endif // TOWERVM_MACHINE_H
