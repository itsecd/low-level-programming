default rel

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
    sub rsp, 24+8 ; a,b,c,d + alignment
    
    lea rdi, [msg]
    call puts
    
    lea rdi, [fmt]
    lea rsi, [rbp-4]
    lea rdx, [rbp-8]
    lea rcx, [rbp-16]
    lea r8, [rbp-24]
   
    call scanf
    
    movsx rsi, dword[rbp-4]
    sub rsi, [rbp-16]
    
    cvtss2sd xmm0, [rbp-8]
    mulsd xmm0, [rbp-24]
    mov eax, 1
    
    lea rdi, [fmt2]
    call printf
    

    leave
    xor eax, eax
    ret
    