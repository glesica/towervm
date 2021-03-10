#include "console_device.h"
#include "../../libraries/console.h"

Word execute_ech(const Word *data, size_t data_len) {
  for (size_t i = 0; i < data_len; i++) {
    char c = (char)data[i];
    printf("%c", c);
  }

  return 0;
}

Word console_advance_impl(Word inst, Word *data, size_t data_len) {
  Word code;
  switch (inst) {
  case ECH:
    code = execute_ech(data, data_len);
    break;
  default:
    code = 10;
  }

  return code;
}

Dev console_device_value = {
    .id = 0,
    .impl = console_advance_impl,
};

Dev *console_device = &console_device_value;
