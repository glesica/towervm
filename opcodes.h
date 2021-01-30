// Opcodes used by the machine

#ifndef TOWERVM_OPCODES_H
#define TOWERVM_OPCODES_H

#include "memory.h"

typedef mem_value opcode;

// ------------------------------------
// Math
// ------------------------------------

/**
 * Add the value stored in a register to the value
 * stored in another register and store the
 * result in the second register.
 * ADD_RR <reg_0> <reg_1>
 */
const opcode ADD_RR = 0;

/**
 * Add the literal value to the value stored in the
 * given register and store the result back in that
 * same register.
 * ADD_LR <value> <reg>
 */
const opcode ADD_LR = 1;

/**
 * Subtract the value stored in a register from
 * the value stored in another register and store
 * the result in the second register.
 * SUB_RR <reg_0> <reg_1>
 */
const opcode SUB_RR = 2;

/**
 * Subtract a literal value from the value stored in
 * the given register and store the result back in
 * that same register.
 * SUB_LR <value> <reg>
 */
const opcode SUB_LR = 3;

// ------------------------------------
// Memory
// ------------------------------------

/**
 * Store literal data at a memory address
 * DAT <addr> <value>
 */
const opcode DAT = 100;

/**
 * Clear a register and use it to store a
 * literal value.
 * CLR <reg> <value>
 */
const opcode CLR = 101;

/**
 * Store a register value at a memory address
 * STO <reg> <addr>
 */
const opcode STO = 102;

/**
 * Load a memory address into a register
 * LOD <addr> <reg>
 */
const opcode LOD = 103;

// ------------------------------------
// Flow
// ------------------------------------

/**
 * Jump to the given address if the values in
 * the given registers are not equal.
 * JNE <addr> <reg_0> <reg_1>
 */
const opcode JNE = 200;

/**
 * Jump to the given memory address and continue
 * program execution.
 * JMP <addr>
 */
const opcode JMP = 201;

/**
 * Put the machine into a stopped state where no
 * further execution will take place.
 * STP
 */
const opcode STP = 202;

#endif // TOWERVM_OPCODES_H
