#include "../machine.h"
#include "../opcodes.h"

#include "asserts.h"

int main() {
  machine m;

  m = {};
  m.reg[0] = 1;
  m.reg[1] = 0;
  m.mem[0] = ADD_RR;
  m.mem[1] = 0;
  m.mem[2] = 1;
  execute(&m);
  ASSERT_INT_EQ(m.reg[1], 1, "ADD_RR 1 increments acc")

  m = {};
  m.reg[0] = 1;
  m.reg[1] = 0;
  m.mem[0] = SUB_RR;
  m.mem[1] = 0;
  m.mem[2] = 1;
  execute(&m);
  ASSERT_INT_EQ(m.reg[1], -1, "SUB_RR 1 decrements acc")

  m = {};
  m.mem[0] = DAT;
  m.mem[1] = 3;
  m.mem[2] = 10;
  m.mem[3] = 0;
  execute(&m);
  ASSERT_INT_EQ(m.mem[3], 10, "DAT stores a value at an address")
}
