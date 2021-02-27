# TowerVM Tools

The following TowerVM tools are currently implemented in Python.

## Assembler

Contained in `assemble.py`. Can be run from the command line. See `--help` for
usage. This script generates a binary that can be loaded into TowerVM and run.

## Source Generator

The `generate.py` script looks at the instruction definitions in
`instructions.toml` in the project root and generates Python and C files that
match those definitions. Eventually, it will also be able to generate
documentation. See `--help` for details.

There are CMake custom targets to generate C and Python files.

Eventually, this script will be updated to use the type found in
`instruction.py` to make it easier to output documentation in addition to richer
Python code.

## Other Files

Other Python files are library code used by the tools described above.

  - `context.py` - assembler context container
  - `parse.py` - assembly language parser
  - `word.py` - machine word data type used by the assembler
  - `library.py` - class to represent an instruction library
  - `instruction.py` - class to represent a single instruction
  - `instructions.py` is generated and contains machine instructions
