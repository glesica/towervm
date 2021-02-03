#ifndef TOWERVM_ERRORS_H
#define TOWERVM_ERRORS_H

#include <cstdint>

// ------------------------------------
// Machine errors
// ------------------------------------

typedef enum {
  InvalidAddressError = 0,
  InvalidRegisterError,
  InvalidOpError,
  MachineStoppedError,
  NoMachineError,
} machine_error_kind;

extern const char *machine_error_names[5];

typedef struct {
  machine_error_kind kind;
  // uint64_t line;
} machine_error;

const machine_error no_machine_error = {.kind = NoMachineError};

// ------------------------------------
// Parser errors
// ------------------------------------

typedef enum {
  BlankLineError = 0,
  CommentError,
  MalformedOpNameError,
  NoParserError,
} parser_error_kind;

extern const char *parser_error_names[4];

typedef struct {
  parser_error_kind kind;
} parser_error;

const parser_error no_parser_error = {.kind = NoParserError};

// ------------------------------------
// Assembler errors
// ------------------------------------

typedef enum {
  NoAssemblerError,
} assembler_error_kind;

extern const char *assembler_error_names[1];

typedef struct {
  assembler_error_kind kind;
} assembler_error;

const assembler_error no_assembler_error = {.kind = NoAssemblerError};

#endif // TOWERVM_ERRORS_H
