%include "io64.inc"

section .rodata
    msg1: db "INT: ", 0
    msg2: db "UINT: ", 0
    msg3: db "HEX UINT: 0x", 0
    
    not: db "NOT ", 0
    less: db "LESS THAN 10", 0
    below: db "BELOW THAN 10", 0
    equal: db "EQUAL TO 10", 0
    zero: db "ZERO", 0
    

section .bss
    a: resd 1
    b: resd 1

section .text
global main
main:
    GET_DEC 4, eax
    
    PRINT_STRING msg1
    PRINT_DEC 4, eax
    NEWLINE
    
    PRINT_STRING msg2
    PRINT_UDEC 4, eax
    NEWLINE
    
    PRINT_STRING msg3
    PRINT_HEX 4, eax
    NEWLINE
    
    cmp eax, 10
    jl .less  
    PRINT_STRING [not]  
.less:
    PRINT_STRING [less]
    NEWLINE
    
    jb .below
    PRINT_STRING [not]
.below:
    PRINT_STRING [below]
    NEWLINE
    
    je .equal
    PRINT_STRING [not]
.equal:
    PRINT_STRING [equal]
    NEWLINE
    
    test eax, eax
    jz .zero
    PRINT_STRING [not]
.zero:
    PRINT_STRING [zero]
    NEWLINE
    
    
    xor rax, rax
    ret