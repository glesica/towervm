#!/usr/bin/env bash

set -e

C_FILES=$(find -E src -type f -regex '.*\.(c|cpp|h|hpp)')
C_TEST_FILES=$(find -E tests -type f -regex '.*\.(c|cpp|h|hpp)')

echo "formatting..."
echo "$C_FILES"
clang-format -i $C_FILES

echo "formatting..."
echo "$C_TEST_FILES"
clang-format -i $C_TEST_FILES

echo "formatting tools/"
pipenv run black tools/
