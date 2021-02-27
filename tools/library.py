from typing import Dict, Iterable, Optional

from instruction import Instruction


class Library:
    _instructions: Dict[str, Instruction]
    _name: str

    def __init__(self, name: str):
        self._name = name
        self._instructions = {}

    @property
    def instructions(self) -> Iterable[Instruction]:
        return self._instructions.values()

    def add_instruction(self, name: str, instruction: Instruction) -> None:
        self._instructions[name] = instruction

    def instruction_for(self, instruction: str) -> Optional[Instruction]:
        if instruction in self._instructions:
            return self._instructions[instruction]
        else:
            return None
