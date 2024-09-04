%include "io64.inc"

section .bss
buffer: resb 4096

section .text
global main
main:
    ; count - RCX
    ; x - RAX
    GET_STRING buffer, 4096
    xor rcx, rcx
.cycle_start:
    movsx rax,byte buffer[rcx]  ; same as [buffer+rcx]
    
    test rax, rax        ; check for 0
    jz .cycle_end
    
    cmp rax, 10          ; check for \n
    je .cycle_end
    
    cmp rax, 13          ; check for \r
    je .cycle_end
    
    add rcx, 1
    jmp .cycle_start
.cycle_end:
    PRINT_DEC 8, rcx
    xor rax, rax
    ret