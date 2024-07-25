; RUN: opt -load-pass-plugin %shlibdir/lib2_BasicBlocksCount.so --passes="2_basic-blocks-count" < %s 2>&1 | FileCheck %s

define void @singleBasicBlock() {
; CHECK: Function name: singleBasicBlock
; CHECK-NEXT: Basic blocks count: 1
entry:
  ret void
}

define i32 @multipleBasicBlocks(i32 %x) {
; CHECK: Function name: multipleBasicBlocks
; CHECK-NEXT: Basic blocks count: 3
entry:
  %cmp = icmp eq i32 %x, 0
  br i1 %cmp, label %if.then, label %if.else

if.then:
  ret i32 1

if.else:
  ret i32 0
}
