# Assembly Language

A TowerVM assembly program consists of a whitespace-delimited sequence of
instructions, macros, and literals. Anything following a `%` is considered
a comment and ignored entirely.

## Instructions

The ASCII representation of any instruction code may be used in an assembly
program. They must use ALL CAPS. Note that each instruction consists of exactly
three characters.

See the list of instructions and their descriptions in the same directory as
this file.

## Macros

There are a number of macros available to simplify certain tasks. These are
processed directly by the assembler and end up being replaced by zero or more
machine instructions.

### `FILL`

Syntax: `FILL:<N>:<V>`

Fills a region of memory `N` words long with a particular value, `V`. For
example, `FILL:5:0` is the equivalent of `0 0 0 0 0`. This is useful for
reserving a long block of contiguous memory for use by the program.

### `LABEL`

Syntax: `LABEL:<L>`

Assigns a text label to a position in memory for ease of reference elsewhere in
the program. The label can then be used anywhere a value can be used (for
example, it can be pushed on to the stack before a jump) and it will be replaced
with the correct literal when the program is assembled.

### `START`

Syntax: `START`

This macro denotes the position in the program where execution should begin.
During assembly, its position is recorded and included in the header metadata
prepended to the binary. A valid program MUST include exactly one `START` macro
usage.

## Literals

Right now, only 32 bit integer literals are supported, but they may be written
in a variety of ways:

  * Binary: `0b0101`
  * Octal: `0o14`
  * Decimal: `73`
  * Hex: `0xb4`

## Example

A simple example program is shown below. There are additional examples in the
`examples/` directory at the root of the project.

```
% Simple example program that adds two numbers (a + b)
LABEL:a 5
LABEL:b 7

START
PSH $a     % Push a
PSH $b     % Push b
ADD        % Add the top two stack values
END
```

Note that the syntax is extremely simple and flexible. The example above uses
one line per instruction, but the middle three lines of the program could just
as easily be written `PSH $a PSH $b ADD` to improve clarity, if desired.
