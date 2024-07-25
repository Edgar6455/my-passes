#!/bin/bash

ROOT_DIR=$(dirname "$(dirname "$(realpath "$0")")")

IR_FILENAME_C="example.c"
IR_FILENAME_LL="example.ll"

cd "$ROOT_DIR" || exit

# These 2 lines are optional, you can comment them if you already did them
./scripts/build.sh  # Build the passes
clang -O0 -S -emit-llvm "$IR_FILENAME_C" -o "$IR_FILENAME_LL" # Generate IR of the source file

# Running each pass on that IR
echo -e "------------------------ Running Pass 1 ------------------------\n"
opt -load-pass-plugin "$ROOT_DIR"/lib/lib1_Functions.so --passes="1_functions" -disable-output "$IR_FILENAME_LL"
echo -e "\n------------------------ Running Pass 2 ------------------------\n"
opt -load-pass-plugin "$ROOT_DIR"/lib/lib2_BasicBlocksCount.so --passes="2_basic-blocks-count" -disable-output "$IR_FILENAME_LL"
echo -e "\n------------------------ Running Pass 3 ------------------------\n"
opt -load-pass-plugin "$ROOT_DIR"/lib/lib3_InstructionsInBB.so --passes="3_instructions-in-bb" -disable-output "$IR_FILENAME_LL"
echo -e "\n------------------------ Running Pass 4 ------------------------\n"
opt -load-pass-plugin "$ROOT_DIR"/lib/lib4_Opcodes.so --passes="4_opcodes" -disable-output "$IR_FILENAME_LL"
echo -e "\n------------------------ Running Pass 5 ------------------------\n"
opt -load-pass-plugin "$ROOT_DIR"/lib/lib5_FunctionCallsCount.so --passes="5_function-calls-count" -disable-output "$IR_FILENAME_LL"
echo -e "\n------------------------ Running Pass 6 ------------------------"
echo -e "Note: writing output to output-for-add-to-sub.ll\n"
opt -load-pass-plugin "$ROOT_DIR"/lib/lib6_AddToSub.so --passes="6_add-to-sub" -disable-output "$IR_FILENAME_LL"
