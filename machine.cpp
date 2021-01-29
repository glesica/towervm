#include <cassert>

#include "machine.h"
#include "opcodes.h"

#define VALIDATE_REG(M, R)                                                     \
  if ((R) < 0 || (R) >= REG_COUNT(M)) {                                        \
    return {                                                                   \
        .kind = InvalidRegisterError,                                          \
    };                                                                         \
  }

#define VALIDATE_ADDR(M, A)                                                    \
  if (A < 0 || A >= MEM_SIZE(M)) {                                             \
    return {                                                                   \
        .kind = InvalidAddressError,                                           \
    };                                                                         \
  }

machine_error execute_arith(machine *m, opcode op) {
  mem_value arg_reg = OP_ARG(m);
  VALIDATE_REG(m, arg_reg)

  switch (op) {
  case ADD:
    m->acc += m->reg[arg_reg];
    break;
  case SUB:
    m->acc -= m->reg[arg_reg];
    break;
  default:
    // Should be unreachable because it should never
    // be called with an incompatible op and doing so
    // represents a bug in the VM.
    assert(false);
  }

  return no_error;
}

machine_error execute_dat(machine *m) {
  mem_value arg_addr = OP_ARG(m);
  VALIDATE_ADDR(m, arg_addr)

  mem_value arg_data = OP_ARG(m);

  m->mem[arg_addr] = arg_data;

  return no_error;
}

machine_error execute_sto(machine *m) {
  mem_value arg_reg = OP_ARG(m);
  VALIDATE_REG(m, arg_reg)

  mem_value arg_addr = OP_ARG(m);
  VALIDATE_ADDR(m, arg_addr)

  m->mem[arg_addr] = m->reg[arg_reg];

  return no_error;
}

machine_error execute_lod(machine *m) {
  mem_value arg_addr = OP_ARG(m);
  VALIDATE_ADDR(m, arg_addr)

  mem_value arg_reg = OP_ARG(m);
  VALIDATE_REG(m, arg_reg)

  m->reg[arg_reg] = m->mem[arg_addr];

  return no_error;
}

machine_error execute(machine *m) {
  mem_value op = m->mem[m->pc];
  machine_error err;
  switch (op) {
  case ADD:
  case SUB:
    err = execute_arith(m, op);
    break;
  case DAT:
    err = execute_dat(m);
    break;
  case STO:
    err = execute_sto(m);
    break;
  case LOD:
    err = execute_lod(m);
    break;
  default:
    return {
        .kind = InvalidOpError,
    };
  }

  m->pc += 1;
  return err;
}

void load_program(machine *m, const mem_value values[], uint64_t value_count) {
  assert(value_count <= MEM_SIZE(m));

  // Zero out all the things

  m->acc = 0;
  m->pc = 0;
  for (int &i : m->reg) {
    i = 0;
  }
  for (int &i : m->mem) {
    i = 0;
  }

  // Load the new memory image

  for (uint64_t i = 0; i < value_count; i++) {
    m->mem[i] = values[i];
  }
}
