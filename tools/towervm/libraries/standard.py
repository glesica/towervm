# GENERATED CODE - DO NOT MODIFY

from typing import Dict

from ..instruction import Instruction as I

instructions: Dict[str, I] = {
    "END": I("END", 0, "marker", "marker for the end of execution", "end"),
    "ADD": I("ADD", 1000, "arithmetic", "add the first two values on the stack", "add"),
    "SUB": I(
        "SUB",
        1010,
        "arithmetic",
        "subtract the second value on the stack from the first",
        "subtract",
    ),
    "EQU": I(
        "EQU",
        2000,
        "comparison",
        "compare the first two values on the stack for equality",
        "equal",
    ),
    "CMP": I(
        "CMP",
        2010,
        "comparison",
        "compare first two values on the stack and set -1 if the first is greater, etc",
        "compare",
    ),
    "NOT": I(
        "NOT",
        3000,
        "logical",
        "logically invert the value at the top of the stack",
        "not",
    ),
    "JNZ": I(
        "JNZ",
        4000,
        "jump",
        "jump to the address at the top of the stack if the second value on the stack is non-zero",
        "jump non-zero",
    ),
    "JNE": I(
        "JNE",
        4010,
        "jump",
        "jump if the next two values on the stack are equal",
        "jump not-equal",
    ),
    "JGT": I(
        "JGT",
        4020,
        "jump",
        "jump if the second value on the stack is greater than the third value",
        "jump greater-than",
    ),
    "JLT": I(
        "JLT",
        4030,
        "jump",
        "jump if the value at the top of the stack is less than the next value",
        "jump less-than",
    ),
    "REA": I(
        "REA",
        5000,
        "memory",
        "read from the memory location pointed at by the value at the top of the stack and push its value",
        "read",
    ),
    "WRI": I(
        "WRI",
        5010,
        "memory",
        "write the second value on the stack to the memory location pointed at by the value at the top of the stack",
        "write",
    ),
    "REN": I(
        "REN",
        5020,
        "memory",
        "read from the memory location pointed to by the value at the top of the stack, and read a number of words given by the second value on the stack",
        "read to length",
    ),
    "WEN": I(
        "WEN",
        5030,
        "memory",
        "write a number of values corresponding to the second value on the stack (they will be popped) to the range of memory starting at the location pointed to by the value at the top of the stack",
        "write to length",
    ),
    "PSH": I("PSH", 6000, "stack", "push a value on to the top of the stack", "push"),
    "DIN": I("DIN", 7000, "device", "trigger a device interrupt", "device interrupt"),
}
