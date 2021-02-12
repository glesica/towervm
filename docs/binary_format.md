# Binary Format

A program consists of a sequence of 32 bit words. The program will be loaded
into memory verbatim. Integer values and instructions will be assumed to be
encoded in little-endian format. The beginning of the program can contain data
for later reference and execution will start at the location of the `STA`
instruction and end at the location of the `END` instruction.

Certain instructions are assumed to be followed by relevant data, `PSH` in
particular, but most use the values on the stack as their arguments.
