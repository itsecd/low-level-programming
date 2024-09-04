%include "io64.inc"

section .rodata
arr: dd 1, 2, 3, 4, 5

message1: db "Array starts at 0x", 0
message2: db "Array ends at 0x", 0

section .text
global main
main:
    lea rax, [arr]
    PRINT_STRING message1
    PRINT_HEX 8, rax
    NEWLINE

    PRINT_DEC 4, [rax]  ; простое адресное выражение (толко база)
    NEWLINE
    
    mov rax, 4
    PRINT_DEC 4, [arr+rax] ; база +  индекс
    NEWLINE
    
    PRINT_DEC 4, [arr+rax+4] ; база + индекс + смещение
    NEWLINE
    
    mov rax, 3
    PRINT_DEC 4, [arr+4*rax] ; база + индекс с умножением 
    NEWLINE
    
    lea rax, [arr+16]        ; база + смещение
    
    PRINT_DEC 4, [rax]
    NEWLINE
    
    PRINT_STRING message2
    PRINT_HEX 8, rax
    NEWLINE
    
    xor rax, rax
    ret