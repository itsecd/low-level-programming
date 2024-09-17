section .rodata

a: dd 1.0
b: dd 3.0

section .text
global main

set_single_precision:
    mov eax, 3
    shl eax, 8
    not eax
    sub rsp, 8
    fstcw [rsp]
    mov dx, [rsp]
    and dx, ax
    mov [rsp], dx
    fldcw [rsp]
    add rsp, 8
    ret

main:
    ; full precision
    fld dword[a]
    fld dword[b]
    fdiv 
    
    ; single precisionc (x87 FPU)
    call set_single_precision
    fld dword[a]
    fld dword[b]
    fdiv
    
    ; single precision
    movss xmm0, [a]
    divss xmm0, [b]
    sub rsp, 4
    movss [rsp], xmm0
    fld dword[rsp]
    add rsp, 4
    
    nop ; <= поставьте точку останова здесь
    
    ; в ST0 - результат вычислений одинарной точности c помощью SSE (по IEEE-754)
    ; в ST1 - результат вычислений одинарной точности в сопроцессоре
    ; в ST2 - результат вычислений полной точности
    

    fstp st0
    fstp st0
    fstp st0
    
    xor eax, eax
    ret
    