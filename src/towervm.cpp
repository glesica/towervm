#include "devices/console/console_device.h"
#include "machine.h"
#include "memory.h"
#include "program.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("usage: ./towervm <program>\n");
    return 1;
  }

  char *prog_path = argv[1];

  Word program[MEM_SIZE];
  size_t length;

  ProgErr prog_err = open_program(prog_path, program, &length);
  if (prog_err.kind != SuccessProgErr) {
    print_prog_err(prog_err);
    return 10;
  }

  Mach mach = {};
  INIT_MACH(&mach)
  mach.devs[mach.dev_count++] = console_device;

  load_program(&mach, program, length);

  MachErr mach_err = run(&mach);
  if (mach_err.kind != StoppedMachErr) {
    print_mach_err(mach_err);
    return 20;
  }

  printf("Machine:\n");
  print_mach(&mach, 4, 4);

  return 0;
}
