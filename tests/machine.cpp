#include "../src/machine.h"

#include "asserts.h"

int main() {
  machine m;

  m = {};
  int reg_count = REG_COUNT(&m);
  ASSERT_INT_EQ(reg_count, TARGET_REG_COUNT,
                "Macro should return register count");
  int mem_size = MEM_COUNT(&m);
  ASSERT_INT_EQ(mem_size, TARGET_MEM_COUNT, "Macro should return memory count");
}
