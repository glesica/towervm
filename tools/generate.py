#!/usr/bin/env python3

from typing import TextIO


def generate(instructions, target, out_file: TextIO):
    if "comment" in target:
        out_file.write(target["comment"])
        out_file.write(" GENERATED CODE - DO NOT MODIFY\n\n")

    if "prologue" in target and target["prologue"]:
        for line in target["prologue"]:
            out_file.write(f"{line}\n")

    template: str = target["template"]
    for name in instructions:
        inst = instructions[name]
        out_file.write(template.format(name=name, **inst))
        out_file.write("\n")

    if "epilogue" in target and target["epilogue"]:
        for line in target["epilogue"]:
            out_file.write(f"{line}\n")
    else:
        out_file.write("\n")


if __name__ == "__main__":

    def main():
        from argparse import ArgumentParser
        from sys import argv

        import toml

        arg_parser = ArgumentParser(
            "generate.py",
            description="TowerVM instruction generator",
        )
        arg_parser.add_argument(
            "--targets",
            type=str,
            default="generator_targets.toml",
            help="target definitions",
        )
        arg_parser.add_argument(
            "input",
            type=str,
            help="instruction definitions",
        )
        arg_parser.add_argument(
            "output",
            type=str,
            help="output file to create",
        )
        args = arg_parser.parse_args(argv[1:])

        in_path: str = args.input
        out_path: str = args.output
        targets_path: str = args.targets

        with open(in_path, "r") as in_file:
            defs = toml.load(in_file)

        with open(targets_path, "r") as targets_file:
            targets = toml.load(targets_file)

        target = None
        if out_path.endswith(".h"):
            target = targets["targets"]["c"]
        if out_path.endswith(".hpp"):
            target = targets["targets"]["c"]
        if out_path.endswith(".py"):
            target = targets["targets"]["py"]

        if target is None:
            raise ValueError("no valid target found")

        with open(out_path, "w") as out_file:
            generate(defs, target, out_file)

    main()
