; RUN: opt -load-pass-plugin %shlibdir/lib6_AddToSub.so --passes="6_add-to-sub" < %s -o /dev/null
; RUN: FileCheck --input-file=output-for-add-to-sub.ll %s

define i32 @funcWithAdd(i32 %a, i32 %b) {
; CHECK: define i32 @funcWithAdd(i32 %a, i32 %b) {
; CHECK: %add = sub i32 %a, %b
; CHECK: ret i32 %add
  %add = sub i32 %a, %b
  ret i32 %add
}

define i32 @funcWithMultipleAdds(i32 %a, i32 %b, i32 %c) {
; CHECK: define i32 @funcWithMultipleAdds(i32 %a, i32 %b, i32 %c) {
; CHECK: %add1 = sub i32 %a, %b
; CHECK: %add2 = sub i32 %add1, %c
; CHECK: ret i32 %add2
  %add1 = add i32 %a, %b
  %add2 = add i32 %add1, %c
  ret i32 %add2
}

define i32 @funcWithNoAdds(i32 %a, i32 %b) {
; CHECK: define i32 @funcWithNoAdds(i32 %a, i32 %b) {
; CHECK: ret i32 %a
  ret i32 %a
}
