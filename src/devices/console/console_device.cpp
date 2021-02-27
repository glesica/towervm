#include "console_device.h"
#include "instructions.h"

MachErr execute_ech(Mach *m) {
  POP(m, start)
  POP(m, length)

  for (size_t i = 0; i < length; i++) {
    READ_DATA(m, start + i, word)
    printf("%d ", word);
  }

  PUSH(m, 0) // Garbage memory address
  PUSH(m, 0) // Zero length data
  PUSH(m, 0) // Success

  return success_mach_err;
}

MachErr console_advance_impl(Mach *m) {
  POP(m, inst)

  MachErr err;
  switch (inst) {
  case ECH:
    err = execute_ech(m);
    break;
  default:
    err = invalid_op_mach_err;
  }

  return err;
}

Adv console_advance = console_advance_impl;
