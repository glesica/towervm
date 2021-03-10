#!/usr/bin/env bash

set -e

C_FILES=$(find -E src -type f -regex '.*\.(c|cpp|h|hpp)')
C_TEST_FILES=$(find -E tests -type f -regex '.*\.(c|cpp|h|hpp)')

echo "checking..."
echo "$C_FILES"
clang-format --dry-run --Werror $C_TEST_FILES

echo "checking..."
echo "$C_TEST_FILES"
clang-format --dry-run --Werror $C_FILES

echo "checking tools/"
pipenv run black --check tools/
