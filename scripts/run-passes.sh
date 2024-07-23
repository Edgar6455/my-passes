#!/bin/bash

export LLVM_DIR=/path/to/llvm-project  # Change this to your LLVM root directory path
LLVM_BUILD_DIR="$LLVM_DIR/build"  # Assuming that LLVM build directory called "build", change if something else
ROOT_DIR=$(dirname "$(dirname "$(realpath "$0")")")

IR_FILENAME_C="example.c"
IR_FILENAME_LL="example.ll"

cd "$ROOT_DIR" || exit

# These 2 lines are optional, you can comment them if you already did them
./scripts/build.sh  # Build the passes
"$LLVM_BUILD_DIR"/bin/clang -O0 -S -emit-llvm "$IR_FILENAME_C" -o "$IR_FILENAME_LL" # Generate IR of the source file

# Running each pass on that IR
echo -e "------------------------ Running Pass 1 ------------------------\n"
"$LLVM_BUILD_DIR"/bin/opt -load-pass-plugin "$ROOT_DIR"/lib/lib1_Functions.so --passes="1_functions" -disable-output "$IR_FILENAME_LL"
echo -e "\n------------------------ Running Pass 2 ------------------------\n"
"$LLVM_BUILD_DIR"/bin/opt -load-pass-plugin "$ROOT_DIR"/lib/lib2_BasicBlocksCount.so --passes="2_basic-blocks-count" -disable-output "$IR_FILENAME_LL"
echo -e "\n------------------------ Running Pass 3 ------------------------\n"
"$LLVM_BUILD_DIR"/bin/opt -load-pass-plugin "$ROOT_DIR"/lib/lib3_InstructionsInBB.so --passes="3_instructions-in-bb" -disable-output "$IR_FILENAME_LL"
echo -e "\n------------------------ Running Pass 4 ------------------------\n"
"$LLVM_BUILD_DIR"/bin/opt -load-pass-plugin "$ROOT_DIR"/lib/lib4_Opcodes.so --passes="4_opcodes" -disable-output "$IR_FILENAME_LL"
echo -e "\n------------------------ Running Pass 5 ------------------------\n"
"$LLVM_BUILD_DIR"/bin/opt -load-pass-plugin "$ROOT_DIR"/lib/lib5_FunctionCallsCount.so --passes="5_function-calls-count" -disable-output "$IR_FILENAME_LL"
echo -e "\n------------------------ Running Pass 6 ------------------------"
echo -e "Note: writing output to output-for-add-to-sub.ll\n"
"$LLVM_BUILD_DIR"/bin/opt -load-pass-plugin "$ROOT_DIR"/lib/lib6_AddToSub.so --passes="6_add-to-sub" -S "$IR_FILENAME_LL" -o output-for-add-to-sub.ll
