#include "../src/machine.h"

#include "asserts.h"

int main() {
  Mach m;

  m = {};
  INIT_MACH(&m)
  m.ip = 1;

  Word program[] = {2, 3, 4};
  load_program(&m, program, 3);

  ASSERT_INT_EQ(MEM_SIZE - 3, (int)m.ip, "Program counter is reset")
  ASSERT_INT_EQ(2, m.mem[MEM_SIZE - 3], "Program is loaded into memory")
  ASSERT_INT_EQ(3, m.mem[MEM_SIZE - 2], "Program is loaded into memory")
  ASSERT_INT_EQ(4, m.mem[MEM_SIZE - 1], "Program is loaded into memory")
}
