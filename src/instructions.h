// CPU instruction definitions

#ifndef TOWERVM_INSTRUCTIONS_H
#define TOWERVM_INSTRUCTIONS_H

#include "memory.h"

const Word END = 0;

// Arithmetic
const Word ADD = 1000;
const Word SUB = 1010;

// Comparison
const Word EQU = 2000;
const Word NOT = 2010;
const Word CMP = 2020;

// Jumps
const Word JNZ = 3000;
const Word JNE = 3010;
const Word JGT = 3020;
const Word JLT = 3030;

// Memory
const Word REA = 4000;
const Word WRI = 4010;

// Stack
const Word PSH = 5000;

#endif // TOWERVM_INSTRUCTIONS_H
