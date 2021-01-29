#include "../machine.h"

#include "asserts.h"

int main() {
    machine m;

    m = {};
    int reg_count = REG_COUNT(&m);
    ASSERT_INT_EQ(reg_count, 2, "Macro should return register count");
    int mem_size = MEM_SIZE(&m);
    ASSERT_INT_EQ(mem_size, 448, "Macro should return memory count");
}
