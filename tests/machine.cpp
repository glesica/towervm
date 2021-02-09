#include "../src/machine.h"

#include "asserts.h"

MachErr test() {
  Mach m;

  m = {};
  INIT_MACH(&m)

  ASSERT_INT_EQ(0, (int)m.sp, "stack pointer should be zero")
  ASSERT_INT_EQ(0, (int)m.ip, "instruction pointer should be zero")

  PUSH(&m, 5)
  ASSERT_INT_EQ(5, (int)m.stack[0], "push should set the first value")

  POP(&m, v)
  ASSERT_INT_EQ(5, (int)v, "pop should retrieve the value")

  return success_mach_err;
}

int main() { test(); }
