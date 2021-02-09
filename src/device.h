#ifndef TOWERVM_DEVICE_H
#define TOWERVM_DEVICE_H

#include "memory.h"

#define DEVICE_BUS_WIDTH 8

typedef struct {
  Word bus[DEVICE_BUS_WIDTH];
} Dev;

void update(Dev *d);

#endif // TOWERVM_DEVICE_H
