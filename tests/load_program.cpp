#include "../machine.h"

#include "asserts.h"

int main() {
    machine m;

    m = {};
    m.acc = 1;
    m.pc = 1;
    m.reg[0] = 1;
    m.mem[0] = 1;

    mem_value prog[] = {2, 3, 4};
    load_program(&m, prog, 3);

    ASSERT_INT_EQ(m.acc, 0, "Accumulator is reset")
    ASSERT_INT_EQ(m.pc, 0, "Program counter is reset")
    ASSERT_INT_EQ(m.reg[0], 0, "Registers are reset")
    ASSERT_INT_EQ(m.mem[0], 2, "Program is loaded into memory")
    ASSERT_INT_EQ(m.mem[1], 3, "Program is loaded into memory")
    ASSERT_INT_EQ(m.mem[2], 4, "Program is loaded into memory")
}