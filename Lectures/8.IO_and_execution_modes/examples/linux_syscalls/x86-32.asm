; https://chromium.googlesource.com/chromiumos/docs/+/HEAD/constants/syscalls.md#x86-32_bit

section .rodata
str: db "Hello world!", 13,10,0
str_end: db 0 ; use to compute string length

section .text
global main

main:
    push ebx
    xor ebx, ebx    ; fd=0 - write to stdout
    lea ecx, [str]  ; buf = str - what to write
    mov edx, (str_end - str); size of string
    
    mov eax, 4 ; system call No.4 - write
    int 0x80   ; call interrupt vector 0x80 - make the system call
    
    
    pop ebx
    ret
    