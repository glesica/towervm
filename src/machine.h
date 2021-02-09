// Machine state

#ifndef TOWERVM_MACHINE_H
#define TOWERVM_MACHINE_H

#include <array>
#include <cstdint>
#include <cstdlib>

#include "device.h"
#include "memory.h"

// ------------------------------------
// Machine errors
// ------------------------------------

typedef enum {
  InvalidOpMachErr,
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

// ------------------------------------
// Machine definition
// ------------------------------------

#define MEM_SIZE 1024

typedef struct {
  Addr ip;
  Addr sp;
  Word mem[MEM_SIZE];
} Mach;

#define INIT_MACH(M)                                                           \
  (M)->ip = MEM_SIZE;                                                          \
  (M)->sp = 0;

// ------------------------------------
// Stack operations
// ------------------------------------

#define PUSH(M, V) (M)->mem[((M)->sp)++] = V;

#define POP(M, V) Word V = (M)->mem[--((M)->sp)];

// ------------------------------------
// Programming
// ------------------------------------

/**
 * Read the next instruction from memory and advance the instruction pointer.
 *
 * TODO: Validate the pointer position first?
 */
#define READ_INST(M, V) Word V = (M)->mem[((M)->ip)++];

/**
 * Move the instruction pointer to the given location.
 */
#define WRITE_INST(M, V) (M)->ip = V;

/**
 * Read data from memory.
 *
 * TODO: Validate the memory address and return error
 */
#define READ_DATA(M, A, V) Word V = (M)->mem[(A)];

/**
 * Write data to memory.
 *
 * TODO: Validate the memory address and return error
 */
#define WRITE_DATA(M, A, V) (M)->mem[(A)] = (V);

/**
 * Advance the machine by one clock cycle, executing an instruction in the
 * process. Note that the instruction in question might only be a PUSH.
 */
MachErr advance(Mach *m);

/**
 * Attach a device to the machine such that programs have access to it.
 */
void attach_device(Mach *m, Dev *d);

/**
 * Reset the machine state to be ready to run a new program and then
 * read the program, as an array of opcodes and data, into the machine.
 * After this function returns the machine is ready to have `execute`
 * called on it.
 */
void load_program(Mach *m, const Word prog[], size_t prog_len);

MachErr run(Mach *m);

#endif // TOWERVM_MACHINE_H
