.intel_syntax noprefix

.globl warnlog
.type warnlog, @function

.rodata
set_color_yellow: .string "\033[0;33m"
set_color_reset: .string "\033[0m"

.text
warnlog:
  push rbp
  push rbx
  mov rbp, rsp
  sub rsp, 8
  xor eax, eax

  mov rbx, rdi

  # set color to yellow 
  lea rdi, [set_color_yellow]
  call printf

  # print the message
  mov rdi, rbx
  call puts

  # reset color 
  lea rdi, [set_color_reset]
  call printf

  xor eax, eax
  add rsp, 8
  pop rbx
  pop rbp
  ret
