#ifndef TOWERVM_PROGRAM_H
#define TOWERVM_PROGRAM_H

#include "machine.h"
#include "memory.h"

/**
 * Reset the machine state to be ready to run a new program. Then read the
 * program into memory, parsing the header along the way. After this function
 * returns the machine is ready to have `advance` called on it.
 */
void load_program(Mach *m, const Word prog[], size_t prog_len);

/**
 * Read a program binary from a file, converting it to a sequence
 * of 32 bit integer values suitable to be loaded into the VM.
 */
size_t open_program(const char *filename, Word prog[MEM_SIZE]);

#endif // TOWERVM_PROGRAM_H
