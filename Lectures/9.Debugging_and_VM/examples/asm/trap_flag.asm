; this program will fail without an attached debugger
; the INT3 (no space) instruction will generate #BP (breakpoint exception)
; this exception is usually expected and handled by the debugger, but not by the program.
; on Linux the #BP exception will be converted to SIGTRAP signal by the OS


section .text
global main


switch_tf:
    pushf 
    mov ax, [rsp]
    xor ax, (1<<8)
    mov [rsp], ax
    popf
    ret ; #DB exception


main:
    push rbp
    mov rbp,rsp
    xor ecx, ecx
    call switch_tf
    inc ecx         ; #DB exception
    inc ecx         ; #DB exception
    inc ecx         ; #DB exception
    call switch_tf  ; #DB exception
    inc ecx         ; no exceptions
    inc ecx
    inc ecx
    leave
    xor eax,eax
    ret
    


    
    
    
    