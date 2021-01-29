// Machine state

#ifndef TOWERVM_MACHINE_H
#define TOWERVM_MACHINE_H

#include <array>
#include <cstdint>
#include <cstdlib>

#include "errors.h"
#include "memory.h"
#include "registers.h"

typedef struct {
  // General purpose registers.
  mem_value reg[2];

  // Accumulator register.
  mem_value acc;

  // Program counter holds the address in memory of the
  // next instruction to be executed.
  uint32_t pc;

  // Main memory where the program and data are stored.
  mem_value mem[448];
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
 * Expands to the next value stored in memory after the current
 * position pointed to by the program counter. Also increments
 * the PC by one so that subsequent invocations continue reading
 * through memory.
 */
#define OP_ARG(M) M->mem[++(M->pc)]

/**
 * Move the program forward by executing one instruction and
 * leaving the machine in a consistent state for the next.
 */
machine_error execute(machine *m);

void load_program(machine *m, const mem_value values[], uint64_t value_count);

#endif // TOWERVM_MACHINE_H
