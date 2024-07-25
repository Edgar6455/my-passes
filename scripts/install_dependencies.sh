#!/bin/bash

# Note: You can specify installation path of the LLVM by this command:
#       export LLVM_DIR="/your/preferred/path/for/llvm"

if [ "$HOME" == "/root" ]; then
    echo "Error: Run the script with sudo -E flag."
    exit 1
fi

if [ -z "$LLVM_DIR" ]; then
    echo "Note: LLVM_DIR environment variable is not set."
    LLVM_DIR="$HOME/llvm"
    echo "Setting LLVM_DIR to $LLVM_DIR"
fi

BUILD_DIRNAME="build"
TOTAL_CORES=$(nproc)
CORES_34=$(( (TOTAL_CORES * 3) / 4 ))

echo "Updating package lists..."
apt update
apt-get update

echo "Installing dependencies..."
apt-get install build-essential gcc g++ nasm -y
apt install cmake git python3 python3-pip -y
pip install --upgrade pip
pip install lit

echo "All dependencies are installed. Installing LLVM here:"
echo "$LLVM_DIR"

mkdir -p "$LLVM_DIR"
cd "$LLVM_DIR" || exit

echo "Cloning LLVM project..."
git clone https://github.com/llvm/llvm-project.git
cd llvm-project || exit
git checkout release/18.x

LLVM_DIR="$LLVM_DIR/llvm-project"

mkdir -p "$BUILD_DIRNAME"
cd "$BUILD_DIRNAME" || exit

echo "Building LLVM..."
cmake -DCMAKE_BUILD_TYPE=Release -DLLVM_TARGETS_TO_BUILD=host -DLLVM_ENABLE_PROJECTS=clang "$LLVM_DIR/llvm"
cmake --build . --parallel "$CORES_34"
make install

echo "export LLVM_DIR=$LLVM_DIR" >> ~/.bashrc
source ~/.bashrc

echo "LLVM installation complete. LLVM_DIR is set to $LLVM_DIR"
