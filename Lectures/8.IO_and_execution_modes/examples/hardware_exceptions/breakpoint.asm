; this program will fail without an attached debugger
; the INT3 (no space) instruction will generate #BP (breakpoint exception)
; this exception is usually expected and handled by the debugger, but not by the program.
; on Linux the #BP exception will be converted to SIGTRAP signal by the OS

section .text
global main
main:
    mov eax, 1
    mov eax, 2
    int3
    mov eax, 3
    xor eax,eax
    ret
    
    