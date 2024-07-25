; RUN: opt -load-pass-plugin %shlibdir/lib4_Opcodes.so --passes="4_opcodes" < %s 2>&1 | FileCheck %s

define i32 @binaryOperations(i32 %a, i32 %b) {
; CHECK: Function: binaryOperations
; CHECK-NEXT: Opcode: %add = add i32 %a, %b
; CHECK-NEXT: Opcode: %sub = sub i32 %a, %b
; CHECK-NEXT: Opcode: %mul = mul i32 %a, %b
entry:
  %add = add i32 %a, %b
  %sub = sub i32 %a, %b
  %mul = mul i32 %a, %b
  ret i32 %add
}

define i32 @mixedOperations(i32 %x, i32 %y) {
; CHECK: Function: mixedOperations
; CHECK-NEXT: Opcode: %add = add i32 %x, %y
; CHECK-NEXT: Opcode: %and = and i32 %x, %y
entry:
  %add = add i32 %x, %y
  %and = and i32 %x, %y
  %icmp = icmp eq i32 %x, %y
  br i1 %icmp, label %if.then, label %if.else

if.then:
  ret i32 1

if.else:
  ret i32 0
}
