class Word:
    """
    A single word in an assembly language program.
    """

    _name: str
    _value: int

    def __init__(self, value: int, name: str = ""):
        if value < 0 or value >= (2 ** 32):
            raise ValueError("value must be a 32 bit int")
        self._value = value
        self._name = name

    def __repr__(self) -> str:
        return f"Word({self._name if self.has_name else self._value})"

    def __str__(self) -> str:
        return f"Word({self._name if self.has_name else self._value})"

    @property
    def as_bytes(self):
        return self._value.to_bytes(4, "little", signed=False)

    @property
    def as_int(self):
        return self._value

    @property
    def has_name(self):
        return self._name != ""

    @property
    def name(self):
        return self._name
