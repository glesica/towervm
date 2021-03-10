#ifndef TOWERVM_PROGRAM_H
#define TOWERVM_PROGRAM_H

#include "machine.h"
#include "memory.h"

typedef enum {
  DevCountProgErr,
  MissingDevProgErr,
  SuccessProgErr,
  TooLongProgErr,
} ProgErrKind;

typedef struct {
  ProgErrKind kind;
} ProgErr;

const ProgErr dev_count_prog_err = {.kind = DevCountProgErr};

const ProgErr missing_dev_err = {.kind = MissingDevProgErr};

const ProgErr success_prog_err = {.kind = SuccessProgErr};

/**
 * Reset the machine state to be ready to run a new program. Then read the
 * program into memory, parsing the header along the way. After this function
 * returns the machine is ready to have `advance` called on it.
 */
ProgErr load_program(Mach *m, const Word prog[], size_t prog_len);

/**
 * Read a program binary from a file, converting it to a sequence
 * of 32 bit integer values suitable to be loaded into the VM.
 */
ProgErr open_program(const char *filename, Word prog[MEM_SIZE],
                     size_t *prog_len);

/**
 * Pretty-print a program error.
 */
void print_prog_err(ProgErr e);

#endif // TOWERVM_PROGRAM_H
