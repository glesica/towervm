#include "../machine.h"
#include "../opcodes.h"

#include "asserts.h"

int main() {
    machine m;

    m = { .acc = 0, .pc = 0 };
    m.reg[0] = 1;
    m.mem[0] = ADD;
    m.mem[1] = 0;
    execute(&m);
    ASSERT_INT_EQ(m.acc, 1, "ADD 1 increments acc")


    m = { .acc = 0, .pc = 0 };
    m.reg[0] = 1;
    m.mem[0] = SUB;
    m.mem[1] = 0;
    execute(&m);
    ASSERT_INT_EQ(m.acc, -1, "SUB 1 decrements acc")

    m = { .acc = 0, .pc = 0 };
    m.mem[0] = DAT;
    m.mem[1] = 3;
    m.mem[2] = 10;
    m.mem[3] = 0;
    execute(&m);
    ASSERT_INT_EQ(m.mem[3], 10, "DAT stores a value at an address")
}
