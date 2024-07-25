#!/bin/bash

BUILD_DIRNAME="build"
ROOT_DIR=$(dirname "$(dirname "$(realpath "$0")")")
TOTAL_CORES=$(nproc)
CORES_34=$(( (TOTAL_CORES * 3) / 4 ))

cd "$ROOT_DIR" || exit
rm -rf "$BUILD_DIRNAME"
mkdir "$BUILD_DIRNAME"
cd "$BUILD_DIRNAME" || exit

cmake "$ROOT_DIR"
make -j "$CORES_34"
make install
