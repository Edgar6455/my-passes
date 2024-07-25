; RUN: opt -load-pass-plugin %shlibdir/lib3_InstructionsInBB.so --passes="3_instructions-in-bb" < %s 2>&1 | FileCheck %s

define i32 @singleBasicBlock(i32 %a, i32 %b) {
; CHECK: Function: singleBasicBlock
; CHECK-NEXT: Basic Block: entry
; CHECK-NEXT: Instruction: %add = add i32 %a, %b
; CHECK-NEXT: Instruction: ret i32 %add
entry:
  %add = add i32 %a, %b
  ret i32 %add
}

define i32 @multipleBasicBlocks(i32 %x) {
; CHECK: Function: multipleBasicBlocks
; CHECK-NEXT: Basic Block: entry
; CHECK-NEXT: Instruction: %cmp = icmp eq i32 %x, 0
; CHECK-NEXT: Instruction: br i1 %cmp, label %if.then, label %if.else
entry:
  %cmp = icmp eq i32 %x, 0
  br i1 %cmp, label %if.then, label %if.else

; CHECK: Basic Block: if.then
; CHECK-NEXT: Instruction: ret i32 1
if.then:
  ret i32 1

; CHECK: Basic Block: if.else
; CHECK-NEXT: Instruction: ret i32 0
if.else:
  ret i32 0
}
