from typing import Dict, Optional, List, Tuple, Iterable

import toml

from library import Library
from instruction import Instruction


class AssemblerContext:
    _devices: Dict[str, int]
    _libraries: List[Library]
    _labels: Dict[str, int]

    def __init__(self):
        self._devices = {}
        self._libraries = []
        self._labels = {}

    @property
    def device_count(self) -> int:
        return len(self._devices)

    @property
    def devices(self) -> Iterable[Tuple[str, int]]:
        yield from self._devices.items()

    @property
    def label_count(self) -> int:
        return len(self._labels)

    def add_device(self, name: str, value: int) -> None:
        self._devices[name] = value

    def add_label(self, name: str, value: int) -> None:
        self._labels[name] = value

    def library_for(self, inst: str) -> Optional[Library]:
        for library in self._libraries:
            if library.instruction_for(inst) is not None:
                return library
        return None

    def load_library(self, ident: str) -> None:
        file = open(ident, "r")
        raw_library = toml.load(file)
        self.read_library(ident, raw_library)

    def read_library(self, ident: str, raw_library: Dict) -> None:
        library = Library(ident)
        for name, raw_instr in raw_library:
            instruction = Instruction(name, **raw_instr)
            library.add_instruction(name, instruction)
        self._libraries.append(library)

    def translate_device(self, name: str) -> Optional[int]:
        if name in self._devices:
            return self._devices[name]
        else:
            return None

    def translate_label(self, name: str) -> Optional[int]:
        if name in self._labels:
            return self._labels[name]
        else:
            return None
