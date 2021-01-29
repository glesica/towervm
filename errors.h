#ifndef TOWERVM_ERRORS_H
#define TOWERVM_ERRORS_H

#include <cstdint>

typedef enum {
  NoError,
  InvalidAddressError,
  InvalidRegisterError,
  InvalidOpError,
} error_kind;

typedef struct {
  error_kind kind;
  // uint64_t line;
} machine_error;

const machine_error no_error = {.kind = NoError};

#endif // TOWERVM_ERRORS_H
