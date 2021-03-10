#include <cstdio>

#include "program.h"

ProgErr load_program(Mach *m, const Word prog[], size_t prog_len) {
  m->sp = 0;

  // Process the header
  size_t header_size = 0;

  // Start address
  m->ip = prog[header_size++];

  // Devices
  Word device_count = prog[header_size++];
  if (device_count > DEVS_SIZE) {
    return dev_count_prog_err;
  }

  for (size_t i = header_size; i < header_size + device_count; i++) {
    Word prog_dev = prog[i];

    bool found = false;
    for (Dev *dev : m->devs) {
      if (prog_dev == dev->id) {
        found = true;
        break;
      }
    }

    if (!found) {
      return missing_dev_err;
    }
  }
  header_size += device_count;

  // Read the program into memory
  for (size_t i = header_size; i < prog_len; i++) {
    m->mem[i - header_size] = prog[i];
  }

  return success_prog_err;
}

// TODO: Add error checking on the file open bit
// TODO: MEM_SIZE is no longer sufficient with the header - make it dynamic?
ProgErr open_program(const char *filename, Word prog[MEM_SIZE],
                     size_t *prog_len) {
  FILE *fp = fopen(filename, "rb");
  size_t word_size = sizeof(Word);
  size_t count = fread(prog, word_size, MEM_SIZE, fp);
  fclose(fp);
  *prog_len = count;
  return success_prog_err;
}

void print_prog_err(ProgErr e) {
  fprintf(stderr, "ProgErr: ");
  switch (e.kind) {
  case DevCountProgErr:
    fprintf(stderr, "DevCountProgErr");
    break;
  case MissingDevProgErr:
    fprintf(stderr, "MissingDevProgErr");
    break;
  case SuccessProgErr:
    fprintf(stderr, "SuccessProgErr");
    break;
  case TooLongProgErr:
    fprintf(stderr, "TooLongProgErr");
    break;
  }

  fprintf(stderr, "\n");
}
