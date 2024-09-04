%include "io64.inc"
section .bss
    tmp: resq 1
    
section .rodata
    msg1:db "signed a*b=", 0
    msg2:db "unsigned a*b=", 0
    msg3:db "signed a/b=", 0
    msg4:db "signed a%b=", 0
    msg5:db "unsigned a/b=", 0
    msg6:db "unsigned a%b=", 0
    
section .text
global main

main:
    GET_DEC 4, ecx
    GET_DEC 4, r8d
    
    mov eax, ecx           ; знаковое умножение
    imul r8d
    mov [tmp], eax
    mov [tmp+4], edx
    
    PRINT_STRING [msg1]
    PRINT_DEC 8, [tmp]
    NEWLINE
    
    mov eax, ecx           ; беззнаковое умножение
    mul r8d
    mov [tmp], eax
    mov [tmp+4], edx
    PRINT_STRING [msg2]
    PRINT_DEC 8, [tmp]
    NEWLINE
    
    mov eax, ecx           ; знаковое деление
    cdq       ; !!! - заполнение EDX знаковым битом EAX
    idiv r8d
    
    
    PRINT_STRING [msg3]
    PRINT_DEC 4, eax
    NEWLINE
    PRINT_STRING [msg4]
    PRINT_DEC 4, edx
    NEWLINE

    mov eax, ecx           ; беззнаковое деление
    xor edx, edx ; !!! - очистка мусора в EDX
    div r8d
    
    PRINT_STRING [msg5]
    PRINT_DEC 4, eax
    NEWLINE
    PRINT_STRING [msg6]
    PRINT_DEC 4, edx
    NEWLINE
    
    xor rax, rax
    ret