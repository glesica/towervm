# Devices

Devices allow programs to interact with the world outside the virtual machine
and they can be essentially anything.

Each device has its own set of instructions. Each set of instructions has a
globally unique identifier. Multiple device implementations can use this
identifier provided they exactly respect the instruction set. Think of an
instruction set as an interface that any device may implement.

Device processing is synchronous. While any device is handling instructions, all
other program and device execution is paused.

Communication between the program and devices use a combination of the stack
and main memory. The process for "calling" a device is described below, followed
by the process for retrieving data from the device.

Data to be passed from a program to a device is stored in main memory. The
length of the data and a pointer to the data should be pushed on to the stack.
Then an instruction, taken from the instruction set implemented by the extant
device to be triggered, is pushed on to the stack. Finally, the device ID is
pushed and a device interrupt is triggered, causing execution to pass to the
device itself.

The stack layout at the point with the interrupt is triggered is shown below.

| ID           |
| Instruction  |
| Data Address |
| Data Length  |

Once the device has finished handling the instruction, the top of the stack will
contain three values (starting from the top): an "exit" code, a data address,
and a data length.

| Exit Code    |
| Data Address |
| Data Length  |

The exit code will be zero if the device completed its work successfully. Other
values may have other device-dependent meanings and do not necessarily mean that
an error occurred.

The data address and data length are identical to those described above. Note,
however, that if the data length is set to zero then the device didn't return
any data. However, the address and length will always exist on the stack, even
if the device had nothing to return.
