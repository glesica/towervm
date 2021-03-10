# GENERATED CODE - DO NOT MODIFY

from typing import Dict

from ..instruction import Instruction as I

instructions: Dict[str, I] = {
    "ECH": I(
        "ECH", 0, "output", "print to the console, interpreting memory as ASCII", "echo"
    ),
    "ECN": I(
        "ECN",
        10,
        "output",
        "exactly like ECH but print a newline at the end",
        "echo with newline",
    ),
}
