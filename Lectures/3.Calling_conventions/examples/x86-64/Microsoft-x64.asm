section .rodata
msg: db "Enter A B C D", 13, 10, 0
fmt:db "%d %f %lld %lf", 0
fmt2: db "A-C, B*D: %lld %f",13, 10, 0

section .text
global main
extern puts, printf, scanf

main:
    push rbp
    mov rbp, rsp
    sub rsp, 24+32+8 ; a,b,c,d+shadow_space+5-th arg
    
    lea rcx, [msg]
    call puts
    
    lea rcx, [fmt]
    lea rdx, [rbp-4]
    lea r8, [rbp-8]
    lea r9, [rbp-16]
    lea rax, [rbp-24]
    mov [rsp+32], rax
    
    call scanf
    
    movsx rdx, dword[rbp-4]
    sub rdx, [rbp-16]
    
    cvtss2sd xmm2, [rbp-8]
    mulsd xmm2, [rbp-24]
    movq r8, xmm2
    
    lea rcx, [fmt2]
    call printf
    

    leave
    xor eax, eax
    ret
    