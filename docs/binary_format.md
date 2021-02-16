# Binary Format

A program consists of a sequence of 32 bit words. The program will be loaded
into memory verbatim. Integer values and instructions will be assumed to be
encoded in little-endian format.

Certain instructions are assumed to be followed by relevant data, `PSH` in
particular, but most use the values on the stack as their arguments.

The beginning of the program can contain data for later reference. Execution
will end at the location of the `END` instruction.

## Header

A valid program must contain a header with certain metadata.

  - The first 32 bit word must contain a little-endian encoded integer value
    that tells the VM where to start program execution. This index is relative
    to the first word after the header.

| 0         | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
| -         | - | - | - | - | - | - | - |
| STA index |   |   |   |   |   |   |   |

