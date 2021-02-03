// ASM program parser

#ifndef TOWERVM_PARSER_H
#define TOWERVM_PARSER_H

#include <cstdlib>

#include "errors.h"
#include "opcodes.h"

parser_error parse_instr(char *instr, opcode *op, mem_value args[],
                         size_t *arg_count);

#endif // TOWERVM_PARSER_H
