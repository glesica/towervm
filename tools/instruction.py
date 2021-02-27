class Instruction:
    _name: str
    _value: int
    _category: str
    _description: str
    _pneumonic: str

    def __init__(self, name: str, value: int, category: str, description: str, pneumonic: str):
        self._name = name
        self._value = value
        self._category = category
        self._description = description
        self._pneumonic = pneumonic

    @property
    def name(self) -> str:
        return self._name

    @property
    def value(self) -> int:
        return self._value

    @property
    def description(self) -> str:
        return self._description

    @property
    def pneumonic(self) -> str:
        return self._pneumonic
