from typing import Iterable, BinaryIO

from word import Word


def assemble_program(program: Iterable[Word], out_file: BinaryIO):
    for inst in program:
        out_file.write(inst.as_bytes)


if __name__ == "__main__":

    def main():
        from argparse import ArgumentParser
        from sys import argv

        from parse import parse_file

        parser = ArgumentParser("assemble.py", description="TowerVM assembler")
        parser.add_argument("input", type=str, help="assembly program code")
        parser.add_argument(
            "--output", type=str, default="", help="name of output binary"
        )

        args = parser.parse_args(argv[1:])

        in_filename = args.input
        with open(in_filename, "r") as in_file:
            program = parse_file(in_file)

        out_filename = args.output
        if not out_filename:
            out_filename = ".".join(in_filename.split(".")[:-1])

        if out_filename == in_filename:
            out_filename += ".out"

        with open(out_filename, "wb") as out_file:
            assemble_program(program, out_file)

    main()
