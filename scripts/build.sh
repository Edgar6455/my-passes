#!/bin/bash

LLVM_ROOT_DIR=$(dirname "$(dirname "$(dirname "$(realpath "$0")")")")
BUILD_DIRNAME="build"
ROOT_DIR=$(dirname "$(dirname "$(realpath "$0")")")
TOTAL_CORES=$(nproc)
CORES_34=$(( (TOTAL_CORES * 3) / 4 ))

cd "$ROOT_DIR" || exit
sudo rm -rf "$BUILD_DIRNAME"
mkdir "$BUILD_DIRNAME"
cd "$BUILD_DIRNAME" || exit

cmake -DLLVM_DIR="$LLVM_ROOT_DIR"/build/lib/cmake/llvm "$LLVM_ROOT_DIR"/my-passes
make -j "$CORES_34"
sudo make install
