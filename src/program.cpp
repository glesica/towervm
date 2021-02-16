#include <cstdio>

#include "program.h"

void load_program(Mach *m, const Word prog[], size_t prog_len) {
  m->sp = 0;

  // Process the header
  m->ip = prog[0];

  // Read the program into memory
  for (size_t i = 1; i < prog_len; i++) {
    m->mem[i - 1] = prog[i];
  }
}

size_t open_program(const char *filename, Word prog[MEM_SIZE]) {
  FILE *fp = fopen(filename, "rb");
  size_t word_size = sizeof(Word);
  size_t count = fread(prog, word_size, MEM_SIZE, fp);
  fclose(fp);
  return count;
}
