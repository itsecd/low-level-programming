section .rodata:
two: dd 2
three: dd 3


section .text
global main

enable_fpu_exception:
    sub rsp, 8
    fstcw [rsp]
    mov eax, 1
    shl eax, 5
    not eax
    and byte[rsp], al ; сброс 6 бита (маска исключения PM)
    fldcw [rsp]
    
    add rsp, 8
    ret

main:

    ; используйте отладчик
    fild dword[two]
    fild dword[three]
    fdiv
    fnop
    
    
    fclex ; сброс флагов исключений
    call enable_fpu_exception
    
    fild dword[two]
    fild dword[three]
    fdiv
    fnop  ; исключение вылетит здесь
    
    fstp st0
    fstp st0
    
    xor rax, rax
    ret