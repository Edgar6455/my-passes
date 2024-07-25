; RUN: opt -load-pass-plugin %shlibdir/lib1_Functions.so --passes="1_functions" < %s 2>&1 | FileCheck %s

define void @testFunction() {
; CHECK: Found function: testFunction
entry:
  ret void
}

define void @anotherFunction() {
; CHECK: Found function: anotherFunction
entry:
  ret void
}
