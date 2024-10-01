section .rodata
msg: db "Enter A B C D", 13, 10, 0
fmt:db "%d %f %lld %lf", 0
fmt2: db "A-C, B*D: %lld %f",13, 10, 0

section .text
global main
extern puts, printf, scanf

; https://www.nasm.us/doc/nasmdoc4.html#section-4.10.2

main:
    %push 
    %stacksize flat64
    %assign %$localsize 0
    %local a:dword, b:dword, c:qword, d:qword
    push rbp
    mov rbp, rsp
    sub rsp, %$localsize+32+8 ; a,b,c,d+shadow_space+5-th arg

    
    lea rcx, [msg]
    call puts
    
    lea rcx, [fmt]
    lea rdx, [a]
    lea r8, [b]
    lea r9, [c]
    lea rax, [d]
    mov [rsp+32], rax
    
    call scanf
    
    movsx rdx, dword[a]
    sub rdx, [c]
    
    cvtss2sd xmm2, [b]
    mulsd xmm2, [d]
    movq r8, xmm2
    
    lea rcx, [fmt2]
    call printf
    

    leave
    xor eax, eax
    ret
%pop
    