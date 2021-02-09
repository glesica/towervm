#include "../src/machine.h"

#include "asserts.h"

int main() {
  Mach m;

  m = {};
  INIT_MACH(&m)

  ASSERT_INT_EQ(0, (int)m.sp, "stack pointer should be zero")
  ASSERT_INT_EQ(MEM_SIZE, (int)m.ip, "instruction pointer should be at the end")

  PUSH(&m, 5)
  ASSERT_INT_EQ(5, (int)m.mem[0], "push should set the first value")

  POP(&m, v)
  ASSERT_INT_EQ(5, (int)v, "pop should retrieve the value")
}
