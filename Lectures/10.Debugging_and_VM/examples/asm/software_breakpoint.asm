; this program will fail without an attached debugger
; the INT3 instruction will generate #BP (breakpoint exception)
; this exception is usually expected and handled by the debugger, but not by the program.
; on Linux the #BP exception will be converted to SIGTRAP signal by the OS


; You can also set hardware breakpoints in the debugger
; For example, in gdb you can use the following sequence
; to watch for any access to the variable named "target" 
; (located in .data section)
; 
; After the program breaks at int3 instruction, write commands:
;
; print &target       
; awatch *(address of target)
; cont 
; cont



section .data
target: db 1


section .rodata
fmt: db "%d", 0

section .text
global main
extern printf
extern scanf
main:
    sub rsp, 8
    
    int3              ; generate #BP -> SIGTRAP
    
    lea rdi, [fmt]
    lea rsi, [rsp]
    call scanf
    
    mov ecx, [rsp]
    mov [target], ecx ; WRITE
    
    
    
    lea rdi, [fmt]
    mov esi, [target] ; READ
    call printf
    
    xor eax,eax
    add rsp, 8
    ret
    


    
    
    
    