#ifndef TOWERVM_ERRORS_H
#define TOWERVM_ERRORS_H

#include <cstdint>

typedef enum {
  InvalidAddressError = 0,
  InvalidRegisterError,
  InvalidOpError,
  MachineStoppedError,
  NoError,
} error_kind;

extern const char *error_names[5];

typedef struct {
  error_kind kind;
  // uint64_t line;
} machine_error;

const machine_error no_error = {.kind = NoError};

#endif // TOWERVM_ERRORS_H
