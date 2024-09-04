%include "io64.inc"

section .text
global main

radix_print:
    ; arguments: 
    ; RSI - x
    ; EDI - radix
    
    ; variables:
    ; RAX - x
    ; RDX - digit
    ; RCX - count
    ; on stack - buffer=rsp
    
    mov rax, rsi
    
    
    sub rsp, 65
    mov rcx, 63
    mov byte[rsp+64], 0
    
.cycle_start:
    xor rdx, rdx
    div rdi
    cmp rdx, 10
    jae .else_label
    add rdx, '0'
    jmp .if_end   
.else_label:
    lea rdx, [rdx+'a'-10]
.if_end:
    mov [rsp+rcx], dl
    sub rcx, 1
    test rax, rax
    jnz .cycle_start
    
    lea rdx, [rsp + rcx + 1]
    PRINT_STRING [rdx]
    NEWLINE
    
    add rsp, 65
    ret
    
    


main:
    ;write your code here
    GET_UDEC 8, rsi
    
    mov rdi, 2
    call radix_print
    mov rdi, 8
    call radix_print
    mov rdi, 10
    call radix_print
    mov rdi, 16
    call radix_print
    mov rdi, 32
    call radix_print
    
    xor rax, rax
    ret