; RUN: opt -load-pass-plugin %shlibdir/lib5_FunctionCallsCount.so --passes="5_function-calls-count" < %s 2>&1 | FileCheck %s

define i32 @funcNoCalls(i32 %x) {
; CHECK: Function: funcNoCalls, Direct Function Call Count: 0
entry:
  %add = add i32 %x, 1
  ret i32 %add
}

define i32 @funcWithCalls(i32 %a, i32 %b) {
; CHECK: Function: funcWithCalls, Direct Function Call Count: 2
entry:
  %call1 = call i32 @someFunction(i32 %a)
  %call2 = call i32 @anotherFunction(i32 %b)
  ret i32 %call1
}

declare i32 @someFunction(i32)
declare i32 @anotherFunction(i32)
