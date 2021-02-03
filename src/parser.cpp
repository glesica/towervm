#include "parser.h"

#define WHITESPACE_CHAR(C) ((C) == ' ' || (C) == '\t')

parser_error parse_instr(const char *instr, char *op, char args[],
                         size_t *arg_count) {
  size_t instr_index = 0;
  char instr_char = instr[instr_index];

  char op_name[4];
  op_name[3] = '\0';

  // First, we burn the leading whitespace
  while (WHITESPACE_CHAR(instr_char)) {
    instr_char = instr[++instr_index];
  }

  // Consume all three op characters at once
  for (size_t i = 0; i < 3; i++) {
    char op_name_char = instr[instr_index + i];

    if (WHITESPACE_CHAR(op_name_char)) {
      return {
          .kind = MalformedOpNameError,
      };
    } else {
      op_name[i] = op_name_char;
    }
  }

  // Now consume all of the args
  while (instr_char != '\0') {
    // Burn whitespace between args
    while (WHITESPACE_CHAR(instr_char)) {
      instr_char = instr[++instr_index];
    }

    // Recover the next arg as a string
    while (!WHITESPACE_CHAR(instr_char)) {
    }
    instr_char = instr[++instr_index];
  }

  // Burn any leading whitespace
  while (WHITESPACE_CHAR(instr_char)) {
    instr_char = instr[++instr_index];
  }

  // If we are at the end of the line then it was blank
  if (instr_char == '\0') {
    return {.kind = BlankLineError};
  }

  // If the line is a comment, ignore it
  if (instr_char == '#') {
    return {.kind = CommentError};
  }

  // Consume the next three characters for the operation

  for (size_t i = 0; i < 3; i++) {
    size_t op_name_index = instr_index += i;
    char op_name_char = instr[op_name_index];

    op_name[i] = op_name_char;
  }

  // TODO: These can be used inside the loop above to simplify
  instr_index += 3;
  instr_char = instr[instr_index];

  // TODO: Should the parser just pass out the operation without validation?
  // Should the parser check the number of args?
  // Figure out a clean way to separate concerns, remember that the assembler
  // exists and can do some of this work. Also remember that the repl needs to
  // be a thing, so maybe the assembler needs to be a library as well so that
  // both the assembler (tool) and repl can use it and the parser can stay
  // simple (dumb) and just convert text to an ast-like data structure.
}
