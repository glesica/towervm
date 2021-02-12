from typing import TextIO, Iterable, Dict

from instructions import instructions
from word import Word


def tokenize_file(file: TextIO) -> Iterable[str]:
    """
    Tokenize the given file based on the TowerVM assembly syntax.
    """
    file.seek(0)

    for line in file:
        # Full line comments
        if line.strip().startswith("%"):
            continue

        for token in line.split():
            # End-of-line comments
            if token.startswith("%"):
                break

            yield token


def parse_file(file: TextIO) -> Iterable[Word]:
    """
    Parse a program written in TowerVM Assembly from a file.

    TODO: Hoist labels so they can be forward-referenced
    TODO: Consider using a true parser for macros

    >>> from io import StringIO as S
    >>> list(parse_file(S("PSH 5 PSH 6 ADD")))
    [Word(PSH), Word(5), Word(PSH), Word(6), Word(ADD)]
    >>> list(parse_file(S('''
    ... PSH 5
    ... PSH 6
    ... ADD''')))
    [Word(PSH), Word(5), Word(PSH), Word(6), Word(ADD)]
    >>> list(parse_file(S("LABEL:foo PSH 6 JNZ $foo")))
    [Word(PSH), Word(6), Word(JNZ), Word(0)]
    >>> list(parse_file(S("FILL:3:0 PSH $foo LABEL:foo")))
    [Word(0), Word(0), Word(0), Word(PSH), Word(5)]
    """
    labels: Dict[str, int] = {}
    mem_counter = 0

    # First pass to calculate positions for LABEL macros so
    # that we can hoist them and allow forward references.
    for token in tokenize_file(file):

        # Update counter for FILL macros
        if token.startswith("FILL:"):
            count = int(token.split(":")[1])
            mem_counter += count
            continue

        # Process LABEL macros fully
        if token.startswith("LABEL:"):
            label = token[6:]
            labels[label] = mem_counter
            continue

        mem_counter += 1

    mem_counter = 0

    # Second pass to process other macros and create the actual
    # Word instances that make up the program.
    for token in tokenize_file(file):

        # FILL macro (expands)
        if token.startswith("FILL:"):
            count = int(token.split(":")[1])
            value = int(token.split(":")[2])
            for word in [Word(value)] * count:
                yield word
            mem_counter += count
            continue

        # Skip LABEL macros
        if token.startswith("LABEL:"):
            continue

        mem_counter += 1

        # Process integer literals
        try:
            value = int(token, base=0)
            yield Word(value)
            continue
        except ValueError:
            pass

        # Process LABEL usages
        if token.startswith("$"):
            label = token[1:]
            value = labels[label]
            yield Word(value)
            continue

        # Process instructions
        try:
            value = instructions[token]
            yield Word(value, name=token)
            continue
        except KeyError:
            pass

        # Token is invalid so bail
        raise ValueError(f"invalid token: {token}")
