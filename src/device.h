#ifndef TOWERVM_DEVICE_H
#define TOWERVM_DEVICE_H

#include "memory.h"

/**
 * A device ID, unique among all devices (or at least all device instruction
 * sets).
 */
typedef Word DevID;

/**
 * A function that implements the behavior of a device. It accepts an
 * instruction, an array of memory values, and the number of memory values
 * available for its use.
 *
 * The return value is an exit code set by the device to indicate whether the
 * instruction succeeded for failed. A zero value indicates success, any other
 * value will be reported as a failure.
 *
 * Each device must implement a compatible function.
 */
typedef Word (*DevImpl)(Word, Word *, size_t);

/**
 * A device, including its ID and implementation function. This can be
 * registered with a machine.
 */
typedef struct {
  DevID id;
  DevImpl impl;
} Dev;

#endif // TOWERVM_DEVICE_H
