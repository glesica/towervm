#include "machine.h"
#include "memory.h"
#include "program.h"

int main() {
  Word program[MEM_SIZE];
  size_t length = open_program("examples/fibonacci", program);

  Mach mach = {};
  INIT_MACH(&mach)

  load_program(&mach, program, length);

  MachErr err = run(&mach);
  //  print_mach_err(err);
  //  print_mach(&mach, 4, 4);
  printf("Result: %d", mach.mem[1]);

  return 0;
}
