#include "machine.h"
#include "libraries/standard.h"

MachErr execute_add(Mach *m) {
  POP(m, a0)
  POP(m, a1)
  auto r = (IntWord)a0 + (IntWord)a1;
  PUSH(m, (Word)r)
  return success_mach_err;
}

MachErr execute_sub(Mach *m) {
  POP(m, s0)
  POP(m, s1)
  auto r = (IntWord)s0 - (IntWord)s1;
  PUSH(m, (Word)r)
  return success_mach_err;
}

MachErr execute_equ(Mach *m) {
  POP(m, b0)
  POP(m, b1)

  Word r;
  if (b0 == b1) {
    r = 1;
  } else {
    r = 0;
  }

  PUSH(m, r)
  return success_mach_err;
}

MachErr execute_not(Mach *m) {
  POP(m, b)
  auto r = !((bool)b);
  PUSH(m, (Word)r)
  return success_mach_err;
}

MachErr execute_cmp(Mach *m) {
  POP(m, _c0)
  POP(m, _c1)
  auto c0 = (IntWord)_c0;
  auto c1 = (IntWord)_c1;

  IntWord r;
  if (c0 == c1) {
    r = 0;
  } else if (c0 > c1) {
    r = 1;
  } else {
    r = -1;
  }

  PUSH(m, (Word)r)
  return success_mach_err;
}

MachErr execute_jnz(Mach *m) {
  POP(m, a)
  POP(m, v)

  if (v != 0) {
    WRITE_INST(m, a)
  }

  return success_mach_err;
}

MachErr execute_jne(Mach *m) {
  POP(m, a)
  POP(m, c0)
  POP(m, c1)

  if (c0 != c1) {
    WRITE_INST(m, a)
  }

  return success_mach_err;
}

MachErr execute_jgt(Mach *m) {
  POP(m, a)
  POP(m, c0)
  POP(m, c1)

  if (c0 > c1) {
    WRITE_INST(m, a)
  }

  return success_mach_err;
}

MachErr execute_jlt(Mach *m) {
  POP(m, a)
  POP(m, c0)
  POP(m, c1)

  if (c0 < c1) {
    WRITE_INST(m, a)
  }

  return success_mach_err;
}

MachErr execute_rea(Mach *m) {
  POP(m, a)
  READ_DATA(m, a, v)
  PUSH(m, v)
  return success_mach_err;
}

MachErr execute_wri(Mach *m) {
  POP(m, a)
  POP(m, v)
  WRITE_DATA(m, a, v)
  return success_mach_err;
}

MachErr execute_psh(Mach *m) {
  READ_INST(m, v)
  PUSH(m, v)
  return success_mach_err;
}

MachErr execute_din(Mach *m) {
  // Read the device ID
  POP(m, did)
  // Read the instruction code
  POP(m, inst)
  // Read memory address
  POP(m, addr)
  // Read memory length
  POP(m, len)

  for (auto &dev : m->devs) {
    if (did == dev->id) {
      Word code = dev->impl(inst, &m->mem[addr], len);
      PUSH(m, code)
      return success_mach_err;
    }
  }

  return invalid_dev_mach_err;
}

MachErr advance(Mach *m) {
  READ_INST(m, inst)

  MachErr err;
  switch (inst) {
  case END:
    err = stopped_mach_err;
    break;
  case ADD:
    err = execute_add(m);
    break;
  case SUB:
    err = execute_sub(m);
    break;
  case EQU:
    err = execute_equ(m);
    break;
  case NOT:
    err = execute_not(m);
    break;
  case CMP:
    err = execute_cmp(m);
    break;
  case JNZ:
    err = execute_jnz(m);
    break;
  case JNE:
    err = execute_jne(m);
    break;
  case JGT:
    err = execute_jgt(m);
    break;
  case JLT:
    err = execute_jlt(m);
    break;
  case REA:
    err = execute_rea(m);
    break;
  case WRI:
    err = execute_wri(m);
    break;
  case PSH:
    err = execute_psh(m);
    break;
  case DIN:
    err = execute_din(m);
    break;
  default:
    err = invalid_op_mach_err;
  }

  return err;
}

MachErr run(Mach *m) {
  MachErr err;
  do {
    // TODO: Choose the correct advance function (devices)
    err = advance(m);
  } while (err.kind == SuccessMachErr);

  return err;
}

void print_mach(Mach *m, size_t stack_count, size_t mem_count) {
  if (stack_count > 0) {
    fprintf(stderr, "stack:\n");
    for (size_t i = 0; i < stack_count; i++) {
      if (i == m->sp) {
        fprintf(stderr, "->");
      } else {
        fprintf(stderr, "  ");
      }
      fprintf(stderr, "  [%zu] = %d\n", i, m->stack[i]);
    }
  }

  if (mem_count > 0) {
    fprintf(stderr, "memory:\n");
    for (size_t i = 0; i < mem_count; i++) {
      if (i == m->ip) {
        fprintf(stderr, "->");
      } else {
        fprintf(stderr, "  ");
      }
      fprintf(stderr, "  [%zu] = %d\n", i, m->mem[i]);
    }
  }
}

void print_mach_err(MachErr e) {
  fprintf(stderr, "MachErr: ");
  switch (e.kind) {
  case InvalidAddrMachErr:
    fprintf(stderr, "InvalidAddrMachErr");
    break;
  case InvalidDevMachErr:
    fprintf(stderr, "InvalidDevMachErr");
    break;
  case InvalidOpMachErr:
    fprintf(stderr, "InvalidOpMachErr");
    break;
  case InvalidStackAddrMachErr:
    fprintf(stderr, "InvalidStackAddrMachErr");
    break;
  case NotImplementedMachErr:
    fprintf(stderr, "NotImplementedMachErr");
    break;
  case StoppedMachErr:
    fprintf(stderr, "StoppedMachErr");
    break;
  case SuccessMachErr:
    fprintf(stderr, "SuccessMachErr");
    break;
  case DeviceMachErr:
    fprintf(stderr, "DeviceMachErr");
    break;
  }

  fprintf(stderr, "\n");
}
