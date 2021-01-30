#include "../machine.h"
#include "../opcodes.h"

// Find the N'th Fibonacci number. Set N here. The
// program to actually find the value is below.
const mem_value N = 5;

const mem_value program[] = {
    CLR, 0, N, // REG0 = N = 4
    CLR, 1, 1, // REG1 = n = 1
    CLR, 2, 0, // REG2 = FIB(n-1)
    CLR, 3, 1, // REG3 = FIB(n)

    // LOOP

    // Buffer = FIB(n-1) + FIB(n)
    CLR, 4, 0,    // REG4 = 0
    ADD_RR, 2, 4, // REG4 += REG2
    ADD_RR, 3, 4, // REG4 += REG3

    // FIB(n-1) = FIB(n)
    CLR, 2, 0,    // REG2 = 0
    ADD_RR, 3, 2, // REG2 = REG3 + REG2

    // FIB(n) = Buffer
    CLR, 3, 0,    // REG3 = 0
    ADD_RR, 4, 3, // REG3 = REG4 + REG3

    // n = n + 1
    ADD_LR, 1, 1, // REG1 = 1 + REG1

    // If n != N Then LOOP
    JNE, 12, 0, 1, // If REG0 != REG1 Then Goto 15

    // Result = REG3
    STP,
};

int main() {
  machine m = {};
  int program_length = sizeof(program) / sizeof(program[0]);
  load_program(&m, program, program_length);

  machine_error err;
  do {
    err = execute(&m);
  } while (err.kind == NoError);

  if (err.kind == MachineStoppedError) {
    printf("result: %d\n", m.reg[3]);
  } else {
    printf("result: %s\n", error_names[(size_t) err.kind]);
    return 1;
  }

  return 0;
}
