#ifndef TOWERVM_ASSEMBLER_H
#define TOWERVM_ASSEMBLER_H

#include "errors.h"

// Accept input from the parser and barf out an array of mem values
// that can be loaded into the vm as a program
// Program may be built up one instruction at a time since that's
// how we're going to parse it to facilitate the repl
// The repl itself will need to load / reload instructions carefully
// so as to maintain state between instructions

assembler_error assemble_instr();

#endif // TOWERVM_ASSEMBLER_H
