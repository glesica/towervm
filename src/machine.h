// Machine state

#ifndef TOWERVM_MACHINE_H
#define TOWERVM_MACHINE_H

#include <array>
#include <cstdint>
#include <cstdlib>

#include "memory.h"

// ------------------------------------
// Machine errors
// ------------------------------------

typedef enum {
  DeviceMachErr,
  InvalidAddrMachErr,
  InvalidOpMachErr,
  InvalidStackAddrMachErr,
  NotImplementedMachErr,
  StoppedMachErr,
  SuccessMachErr,
} MachErrKind;

typedef struct {
  MachErrKind kind;
} MachErr;

const MachErr invalid_op_mach_err = {.kind = InvalidOpMachErr};

const MachErr not_implemented_mach_err = {.kind = NotImplementedMachErr};

const MachErr stopped_mach_err = {.kind = StoppedMachErr};

const MachErr success_mach_err = {.kind = SuccessMachErr};

void print_mach_err(MachErr e);

// ------------------------------------
// Machine definition
// ------------------------------------

#define MEM_SIZE 1024
#define STACK_SIZE 1024
#define DEVS_SIZE 32

typedef struct {
  Addr ip;
  Addr sp;
  Word mem[MEM_SIZE];
  Word stack[STACK_SIZE];
  Word devs[32];
} Mach;

#define INIT_MACH(M)                                                           \
  (M)->ip = 0;                                                                 \
  (M)->sp = 0;

// ------------------------------------
// Stack operations
// ------------------------------------

#define PUSH(M, V)                                                             \
  if (((M)->sp) >= STACK_SIZE || ((M)->sp) < 0) {                              \
    return {                                                                   \
        .kind = InvalidStackAddrMachErr,                                       \
    };                                                                         \
  }                                                                            \
  (M)->stack[((M)->sp)++] = V;

#define POP(M, V)                                                              \
  if (((M)->sp) > STACK_SIZE || ((M)->sp) <= 0) {                              \
    return {                                                                   \
        .kind = InvalidStackAddrMachErr,                                       \
    };                                                                         \
  }                                                                            \
  Word V = (M)->stack[--((M)->sp)];

// ------------------------------------
// Programming
// ------------------------------------

/**
 * Read the next instruction from memory and advance the instruction pointer.
 *
 * TODO: Validate the pointer position first?
 */
#define READ_INST(M, V)                                                        \
  if (((M)->ip) >= MEM_SIZE || ((M)->ip) < 0) {                                \
    return {                                                                   \
        .kind = InvalidAddrMachErr,                                            \
    };                                                                         \
  }                                                                            \
  Word V = (M)->mem[((M)->ip)++];

/**
 * Move the instruction pointer to the given location.
 */
#define WRITE_INST(M, A)                                                       \
  if ((A) >= MEM_SIZE || (A) < 0) {                                            \
    return {                                                                   \
        .kind = InvalidAddrMachErr,                                            \
    };                                                                         \
  }                                                                            \
  (M)->ip = A;

/**
 * Read data from memory.
 *
 * TODO: Validate the memory address and return error
 */
#define READ_DATA(M, A, V)                                                     \
  if ((A) >= MEM_SIZE || (A) < 0) {                                            \
    return {                                                                   \
        .kind = InvalidAddrMachErr,                                            \
    };                                                                         \
  }                                                                            \
  Word V = (M)->mem[(A)];

/**
 * Write data to memory.
 *
 * TODO: Validate the memory address and return error
 */
#define WRITE_DATA(M, A, V)                                                    \
  if ((A) >= MEM_SIZE || (A) < 0) {                                            \
    return {                                                                   \
        .kind = InvalidAddrMachErr,                                            \
    };                                                                         \
  }                                                                            \
  (M)->mem[(A)] = (V);

/**
 * A function that is capable of advancing a machine by one instruction.
 *
 * One implementation exists for the machine itself, and one for each
 * device capable of being attached to the machine.
 */
typedef MachErr (*Adv)(Mach *);

/**
 * Advance the machine by one clock cycle, executing an instruction in the
 * process. Note that the instruction in question might only be a PUSH.
 *
 * This implements the `Adv` type for the virtual machine itself.
 */
MachErr advance(Mach *m);

/**
 * Continue to advance the machine until it signals something other than success
 * (which could be that its program has finished executing).
 */
MachErr run(Mach *m);

/**
 * Pretty-print a machine state. Include the given number of stack and memory
 * elements in the output (this allows the output to be a little tidier since
 * the entire stack and memory range are seldom interesting).
 */
void print_mach(Mach *m, size_t stack_count, size_t mem_count);

#endif // TOWERVM_MACHINE_H
