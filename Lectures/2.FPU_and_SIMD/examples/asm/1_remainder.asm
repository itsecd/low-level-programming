section .rodata:
divident: dq 1.0e+20
divisor: dq 3.0


section .text
global main

true_remainder:
    
.cycle:    
    fprem
    fstsw ax
    test ax, 0x400 ; 0x400 = 0b1000000000 (установлен бит 10, соотв. флагу C2)
    jnz .cycle
    ret
    
main:

    fld qword[divisor]
    fld qword[divident]
    fprem      
    nop ; <= установите точку останова здесь, в ST0 - частичный остаток
    fstp st0
    
    fld qword[divident]
    call true_remainder
    nop ; <= установите точку останова здесь, в ST0 - истинный остаток
    
    fstp st0
    ret
    
    
    


    
    