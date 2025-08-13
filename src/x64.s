.intel_syntax noprefix

.globl warnlog
.type warnlog, @function

.globl asmcat
.type asmcat, @function

.globl asmcpy
.type asmcpy, @function

.globl asmcmp
.type asmcmp, @function

.globl asmlen
.type asmlen, @function

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

asmlen:
  xor eax, eax
.loop:
  cmp BYTE PTR [rdi + rax], 0
  je .len
  inc rax
  jmp .loop
.len:
  ret

asmcpy:
  mov al, BYTE PTR [rsi]
  mov BYTE PTR [rdi], al
  inc rsi
  inc rdi
  cmp al, 0
  jne asmcpy
  ret

asmcat:
  push rdi
  push rsi

  call asmlen
  pop rsi
  pop rdi

  add rdi, rax
  jmp asmcpy

  ret

asmcmp:
  xor eax, eax
  xor ecx, ecx

.loop_cmp:
  lodsb # load byte from [esi] into al, esi++
  cmp al, BYTE PTR [rdi]
  jne .not_equal

  cmp al, 0 
  je .equal

  inc rdi
  jmp .loop_cmp

.not_equal:
  xor eax, eax
  ret

.equal:
  mov eax, 1
  ret

