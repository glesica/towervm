#include <cstdio>
#include <unistd.h>

#include "devices/console/console_device.h"
#include "machine.h"
#include "memory.h"
#include "program.h"

void print_help(FILE *out) {
  fprintf(out, "usage: towervm -[hd] <program>\n\n");
  fprintf(out, "TowerVM runtime tool\n\n");
  fprintf(out, "options:\n");
  fprintf(out, "  -d        print extra debug information\n");
  fprintf(out, "  -h        print help and exit\n");
}

int main(int argc, char *argv[]) {
  bool debug_mode = false;

  int opt;
  while ((opt = getopt(argc, argv, "hd")) != -1) {
    switch (opt) {
    case 'h':
      print_help(stdout);
      return 0;
    case 'd':
      debug_mode = true;
      break;
    default:
      fprintf(stderr, "Invalid option: %d\n", opt);
      print_help(stderr);
      return 1;
    }
  }

  if (optind != argc - 1) {
    fprintf(stderr, "No <program> specified\n");
    print_help(stderr);
    return 1;
  }

  char *prog_path = argv[optind];

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

  if (debug_mode) {
    fprintf(stderr, "Machine:\n");
    print_mach(&mach, 4, 4);
  }

  return 0;
}
