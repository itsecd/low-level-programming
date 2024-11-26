; BUILD IN x86-32 !!!
; Use "Debug" and "Step over" buttons (see above)
section .text
global main
main:
    mov ecx, 0x80000000 ; 
    sub ecx, 1 ; overflow, ecx =0
    into       ; check the OF, if OF=1 - raise hardware exception
    ret
    
    