from re import compile
from typing import TextIO, Iterable

from .context import AssemblerContext
from .libraries.standard import instructions
from .word import Word, MetaWord

DEVICE_MACRO = compile(r"^DEVICE:[a-z]+:\d+$")
STRING_MACRO = compile(r"^STRING:\"(.*)\"$")


# TODO: Add line and token numbers
class ParserError(Exception):
    pass


def tokenize_file(file: TextIO) -> Iterable[str]:
    """
    Tokenize the given file based on the TowerVM assembly syntax.

    TODO: Provide line and character position along with token for errors

    >>> from io import StringIO as S
    >>> list(tokenize_file(S("\\n".join(["PSH 5", "% comment", "ADD"]))))
    ['PSH', '5', 'ADD']
    >>> list(tokenize_file(S("  % comment")))
    []
    >>> list(tokenize_file(S("STRING:\\"A B\\"")))
    ['STRING:"A B"']
    """
    file.seek(0)

    for line in file:
        stripped_line = line.strip()

        # Full line comments
        if stripped_line.startswith("%"):
            continue

        # Import directives (skip until implemented)
        if stripped_line.startswith("#"):
            continue

        chunks = iter(stripped_line.split())
        while True:
            try:
                chunk = next(chunks)
            except StopIteration:
                break
            # End-of-line comments
            # TODO: This could also happen mid-string
            if chunk.startswith("%"):
                break

            # Detect STRING and handle spaces
            if chunk.startswith('STRING:"'):
                # Continue to consume chunks (adding spaces back in) until we
                # have something that matches the regex.
                token = chunk

                while STRING_MACRO.fullmatch(token) is None:
                    try:
                        chunk = next(chunks)
                    except StopIteration:
                        raise ParserError()

                    token = f"{token} {chunk}"

                chunk = token

            yield chunk


def parse_file(file: TextIO) -> Iterable[Word]:
    """
    Parse a program written in TowerVM Assembly from a file.

    TODO: Implement #import directives
    TODO: Add standard instructions as a library to context
    TODO: Implement STRING macro to lay out string in memory
    TODO: Add affordances for passing memory regions to devices

    Should STRING macro pack its data? Maybe. We could do little-endian
    style packing to make reading it back out simpler. But then we still
    have to unpack it, making it harder to work with and harder to debug.
    Stick with no packing for now, we can do that later if we want.

    >>> from io import StringIO as S
    >>> list(parse_file(S("PSH 5 PSH 6 ADD")))
    [Word(device_count=0), Word(PSH), Word(5), Word(PSH), Word(6), Word(ADD)]
    >>> list(parse_file(S('''
    ... PSH 5
    ... PSH 6
    ... ADD''')))
    [Word(device_count=0), Word(PSH), Word(5), Word(PSH), Word(6), Word(ADD)]
    >>> list(parse_file(S("LABEL:foo PSH 6 JNZ $foo")))
    [Word(device_count=0), Word(PSH), Word(6), Word(JNZ), Word(0)]
    >>> list(parse_file(S("FILL:3:0 PSH $foo LABEL:foo")))
    [Word(device_count=0), Word(0), Word(0), Word(0), Word(PSH), Word(5)]
    """
    context = AssemblerContext()
    mem_counter = 0

    # FIRST PASS
    # Determine the size of all expanding macros and calculate the START
    # position ahead of time. Also register symbols that will be used later.
    for token in tokenize_file(file):

        # Update counter for FILL macros
        if token.startswith("FILL:"):
            count = int(token.split(":")[1])
            mem_counter += count
            continue

        # Process DEVICE dependency macros fully
        if DEVICE_MACRO.fullmatch(token) is not None:
            device_name = token.split(":")[1]
            device_id = int(token.split(":")[2])
            context.add_device(device_name, device_id)
            continue

        # Update counter for STRING macros
        string_match = STRING_MACRO.fullmatch(token)
        if string_match is not None:
            value = string_match.group(1)
            mem_counter += len(value)
            continue

        # Process LABEL macros fully
        if token.startswith("LABEL:"):
            label = token[6:]
            context.add_label(label, mem_counter)
            continue

        # Process START macro
        if token == "START":
            yield MetaWord(mem_counter, token)
            continue

        mem_counter += 1

    # Emit all device dependencies now that we can count them.
    yield MetaWord(context.device_count, "device_count")
    for device_name, device_id in context.devices:
        yield Word(device_id, device_name)

    # Re-use this variable since we're going to iterate again. Right now it
    # isn't used in the second loop, but we maintain the invariant from above in
    # case we want to use it in the future.
    mem_counter = 0

    # Second pass to process other macros and create the actual Word instances
    # that make up the program.
    for token in tokenize_file(file):

        # FILL macro (expands)
        if token.startswith("FILL:"):
            count = int(token.split(":")[1])
            value = int(token.split(":")[2])
            for word in [Word(value)] * count:
                yield word
            mem_counter += count
            continue

        # STRING macro (expands)
        string_match = STRING_MACRO.fullmatch(token)
        if string_match is not None:
            value = string_match.group(1)
            for char in value:
                yield Word(ord(char), char)
            mem_counter += len(value)
            continue

        # Skip DEVICE dependency macros
        if DEVICE_MACRO.fullmatch(token) is not None:
            continue

        # Skip LABEL macros
        if token.startswith("LABEL:"):
            continue

        # Skip START macro
        if token.startswith("START"):
            continue

        mem_counter += 1

        # Process integer literals
        try:
            value = int(token, base=0)
            yield Word(value)
            continue
        except ValueError:
            pass

        # Process DEVICE usages
        if token.startswith("&"):
            device = token[1:]
            value = context.translate_device(device)
            if value is None:
                raise ParserError()
            yield Word(value)
            continue

        # Process LABEL usages
        if token.startswith("$"):
            label = token[1:]
            value = context.translate_label(label)
            if value is None:
                raise ParserError()
            yield Word(value)
            continue

        # Process instructions
        try:
            inst = instructions[token]
            yield Word(inst.value, name=token)
            continue
        except KeyError:
            pass

        # Token is invalid so bail
        raise ValueError(f"invalid token: '{token}'")
