#!/bin/bash

BUILD_DIRNAME="build"
ROOT_DIR=$(dirname "$(dirname "$(realpath "$0")")")
TOTAL_CORES=$(nproc)
CORES_34=$(( (TOTAL_CORES * 3) / 4 ))

cd "$ROOT_DIR" || exit
sudo rm -rf "$BUILD_DIRNAME"
mkdir "$BUILD_DIRNAME"
cd "$BUILD_DIRNAME" || exit

cmake -DLLVM_DIR="$LLVM_DIR"/build/lib/cmake/llvm "$ROOT_DIR"
make -j "$CORES_34"
sudo make install
