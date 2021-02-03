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
  if (A < 0 || A >= MEM_COUNT(M)) {                                            \
    return {                                                                   \
        .kind = InvalidAddressError,                                           \
    };                                                                         \
  }

// TODO: Ideally we'd want to share memory between the machine and device
// We still need a way for a device to communicate back to the machine
// We could just maintain a separate ordered list of devices and then run
// through the list after each instruction is executed and allow them to
// do their thing. We don't actually need any links between them. How does
// the machine know that its memory was updated, though? Maybe it just has
// to figure that out for itself. But then we need to go the other
// direction. Should part of the memory be read and part write?
void attach_device(machine *m, device *d) {}

machine_error execute_arith(machine *m, opcode op) {
  READ_PC(m, arg_reg0)
  VALIDATE_REG(m, arg_reg0)

  READ_PC(m, arg_reg1)
  VALIDATE_REG(m, arg_reg1)

  switch (op) {
  case ADD_RR:
    m->reg[arg_reg1] += m->reg[arg_reg0];
    break;
  case SUB_RR:
    m->reg[arg_reg1] -= m->reg[arg_reg0];
    break;
  default:
    // Should be unreachable because it should never
    // be called with an incompatible op and doing so
    // represents a bug in the VM.
    assert(false);
  }

  return no_machine_error;
}

machine_error execute_arith_literal(machine *m, opcode op) {
  READ_PC(m, arg_value)

  READ_PC(m, arg_reg)
  VALIDATE_REG(m, arg_reg)

  switch (op) {
  case ADD_LR:
    m->reg[arg_reg] += arg_value;
    break;
  case SUB_LR:
    m->reg[arg_reg] -= arg_value;
    break;
  default:
    // Should be unreachable because it should never
    // be called with an incompatible op and doing so
    // represents a bug in the VM.
    assert(false);
  }

  return no_machine_error;
}

machine_error execute_dat(machine *m) {
  READ_PC(m, arg_addr)
  VALIDATE_ADDR(m, arg_addr)

  READ_PC(m, arg_data)

  m->mem[arg_addr] = arg_data;

  return no_machine_error;
}

machine_error execute_clr(machine *m) {
  READ_PC(m, reg)
  VALIDATE_REG(m, reg)

  READ_PC(m, arg_data)

  m->reg[reg] = arg_data;

  return no_machine_error;
}

machine_error execute_sto(machine *m) {
  READ_PC(m, arg_reg)
  VALIDATE_REG(m, arg_reg)

  READ_PC(m, arg_addr)
  VALIDATE_ADDR(m, arg_addr)

  m->mem[arg_addr] = m->reg[arg_reg];

  return no_machine_error;
}

machine_error execute_lod(machine *m) {
  READ_PC(m, arg_addr)
  VALIDATE_ADDR(m, arg_addr)

  READ_PC(m, arg_reg)
  VALIDATE_REG(m, arg_reg)

  m->reg[arg_reg] = m->mem[arg_addr];

  return no_machine_error;
}

machine_error execute_jne(machine *m) {
  READ_PC(m, arg_addr)
  VALIDATE_ADDR(m, arg_addr)

  READ_PC(m, arg_reg0)
  VALIDATE_REG(m, arg_reg0)
  mem_value value_reg0 = m->reg[arg_reg0];

  READ_PC(m, arg_reg1)
  VALIDATE_REG(m, arg_reg1)
  mem_value value_reg1 = m->reg[arg_reg1];

  if (value_reg0 != value_reg1) {
    m->pc = arg_addr;
  }

  return no_machine_error;
}

machine_error execute(machine *m) {
  READ_PC(m, op)
  machine_error err;

  switch (op) {
  case ADD_RR:
  case SUB_RR:
    err = execute_arith(m, op);
    break;
  case ADD_LR:
  case SUB_LR:
    err = execute_arith_literal(m, op);
    break;
  case DAT:
    err = execute_dat(m);
    break;
  case CLR:
    err = execute_clr(m);
    break;
  case STO:
    err = execute_sto(m);
    break;
  case LOD:
    err = execute_lod(m);
    break;
  case JNE:
    err = execute_jne(m);
    break;
  case STP:
    err = {
        .kind = MachineStoppedError,
    };
    break;
  default:
    err = {
        .kind = InvalidOpError,
    };
  }

  return err;
}

void load_program(machine *m, const mem_value values[], uint64_t value_count) {
  assert(value_count <= MEM_COUNT(m));

  // Zero out all the things

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
