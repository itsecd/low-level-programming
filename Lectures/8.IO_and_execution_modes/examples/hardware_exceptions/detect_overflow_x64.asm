; BUILD IN x86-64 !!!
; Use "Debug" and "Step over" buttons (see above)
section .text
global main
main:
    mov ecx, 0x80000000 ;  min. negative 32-bit number
    sub ecx, 1 ; overflow, ecx =0
    ; no INTO instruction in x64, condiditional jump is used
    ; check the OF, if OF=1 - raise hardware exception
    jno .ok
    int 4; generate #OF exception
    
   .ok:
    ret
    
    