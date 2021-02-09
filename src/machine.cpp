#include "machine.h"
#include "instructions.h"

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

  if (v == 0) {
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
  READ_INST(m, value)
  PUSH(m, value)
  return success_mach_err;
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
  default:
    err = invalid_op_mach_err;
  }

  return err;
}

// TODO: Error if the program is too large
void load_program(Mach *m, const Word prog[], size_t prog_len) {
  m->ip = MEM_SIZE - prog_len;
  for (size_t i_prog = 0; i_prog < prog_len; i_prog++) {
    auto i_mem = MEM_SIZE - prog_len + i_prog;
    m->mem[i_mem] = prog[i_prog];
  }
}

MachErr run(Mach *m) {
  MachErr err;
  do {
    err = advance(m);
  } while (err.kind == SuccessMachErr);

  return err;
}
