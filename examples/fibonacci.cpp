#include "../src/instructions.h"
#include "../src/machine.h"

// Find the N'th Fibonacci number. Set N here. The
// program to actually find the value is below.
const Word N = 5;

const Word program[] = {
    // TODO: Implement fibonacci
};

int main() {
  Mach m = {};
  int program_length = sizeof(program) / sizeof(program[0]);
  load_program(&m, program, program_length);

  MachErr err;
  do {
    err = advance(&m);
  } while (err.kind == SuccessMachErr);

  if (err.kind == StoppedMachErr) {
    POP(&m, result)
    printf("result: %d\n", result);
  } else {
    printf("result: %s\n", "error name");
    return 1;
  }

  return 0;
}
