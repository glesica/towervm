#include "../src/instructions.h"
#include "../src/machine.h"

#include "asserts.h"

int main() {
  Mach m;

  m = {};
  INIT_MACH(&m)
  m.mem[0] = 3;
  m.mem[1] = 2;
  m.sp = 2;
  m.mem[MEM_SIZE - 1] = ADD;
  m.ip = MEM_SIZE - 1;
  advance(&m);
  ASSERT_INT_EQ(5, m.mem[0], "add two values")

  m = {};
  INIT_MACH(&m)
  m.mem[0] = 2;
  m.mem[1] = 3;
  m.sp = 2;
  m.mem[MEM_SIZE - 1] = SUB;
  m.ip = MEM_SIZE - 1;
  advance(&m);
  ASSERT_INT_EQ(1, m.mem[0], "subtract two values")
}