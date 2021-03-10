#!/usr/bin/env bash

set -e

pipenv run ./tools/generate.py libraries/standard.toml src/libraries/standard.h
pipenv run ./tools/generate.py libraries/standard.toml tools/towervm/libraries/standard.py

pipenv run ./tools/generate.py src/devices/console/console.toml src/libraries/console.h
pipenv run ./tools/generate.py src/devices/console/console.toml tools/towervm/libraries/console.py
