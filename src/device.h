#ifndef TOWERVM_DEVICE_H
#define TOWERVM_DEVICE_H

#include "machine.h"
#include "memory.h"

typedef uint32_t DevID;

typedef struct {
  DevID id;
  Adv advance;
} Dev;

#endif // TOWERVM_DEVICE_H
