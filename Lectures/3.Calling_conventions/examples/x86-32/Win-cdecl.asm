section .rodata
msg: db "Enter A B C D", 13, 10, 0
fmt:db "%d %f %lld %lf", 0
fmt2: db "A-C, B*D: %lld %f",13, 10, 0


section .text
global _WinMain@16
extern _printf
extern _scanf
extern _puts

_WinMain@16:
    push ebp
    mov ebp, esp
    
    sub esp, 4+4+8+8+20 ; a, b, c, d + args
    lea eax, [msg]
    mov [esp], eax
    call _puts
    
    lea eax, [ebp - 24]
    mov [esp + 16], eax
    lea eax, [ebp - 16]
    mov [esp + 12], eax
    lea eax, [ebp - 8]
    mov [esp + 8], eax
    lea eax, [ebp - 4]
    mov [esp + 4], eax
    lea eax, [fmt]
    mov [esp], eax
    call _scanf
        
    fld dword[ebp-8]
    fld qword[ebp-24]
    fmul
    fstp qword[esp+12]

    mov eax, [ebp - 4]
    cdq
    sub eax, [ebp-16]
    sbb edx, [ebp-12]
    
    mov [esp+4], eax
    mov [esp+8], edx

    lea eax, [fmt2]
    mov [esp], eax
    
    call _printf
    
    leave
    xor eax, eax
    ret