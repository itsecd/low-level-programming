; https://chromium.googlesource.com/chromiumos/docs/+/HEAD/constants/syscalls.md#x86_64-64_bit

section .rodata
str: db "Hello world!", 0
str_end: db 0 ; use to compute string length

section .text
global main

main:
    xor edi,edi ; fd=0 - write to stdout
    lea rsi, [str] ; what to write
    mov rdx, (str_end - str) ; size of string (you can substract labels, bc. they are just constants)
    mov eax, 1     ; system call 1 - write
    syscall
    ret