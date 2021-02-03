#ifndef TOWERVM_DEVICE_H
#define TOWERVM_DEVICE_H

#include "memory.h"

#define DEVICE_BUS_WIDTH 8

typedef struct {
  mem_value bus[DEVICE_BUS_WIDTH];
} device;

void update(device *d);

#endif // TOWERVM_DEVICE_H
