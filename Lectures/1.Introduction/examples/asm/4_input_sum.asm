%include "io64.inc"

section .text
global main
main:
    ; count - RCX
    ; result - RAX
    ; x - RDX
    xor rax, rax
    GET_DEC 8, rcx
.cycle_start:
    sub rcx, 1
    js .cycle_end
    GET_DEC 8, rdx
    add rax, rdx
    jmp .cycle_start
.cycle_end:
    PRINT_DEC 8, rax
    
    xor eax,eax
    ret
    