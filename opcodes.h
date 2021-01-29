// Opcodes used by the machine

#ifndef TOWERVM_OPCODES_H
#define TOWERVM_OPCODES_H

#include "memory.h"

typedef mem_value opcode;

// Math
const opcode ADD = 0;
const opcode SUB = 1;

// ------------------------------------
// Memory
// ------------------------------------

// Store literal data at a memory address
// DAT <addr> <value>
const opcode DAT = 100;

// Store a register value at a memory address
// STO <reg> <addr>
const opcode STO = 101;

// Load a memory address into a register
// LOD <addr> <reg>
const opcode LOD = 102;

// Flow
const opcode JNE = 200;
const opcode JMP = 201;

#endif // TOWERVM_OPCODES_H
