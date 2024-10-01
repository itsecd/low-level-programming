section .rodata
    msg: db "Hello, world!",13, 10
    .end: db 0
    STD_OUTPUT_HANDLE: dd -11
    
section .text
    extern _GetStdHandle@4
    extern _WriteConsoleA@20
    extern _ExitProcess@4
    global _WinMain@16

_WinMain@16:
    push ebp
    mov ebp, esp
    push dword[STD_OUTPUT_HANDLE]
    call _GetStdHandle@4
    test eax, eax
    jnz .handle_ok
    push dword -1
    call _ExitProcess@4
    
.handle_ok:
    sub esp, 24         ; args + buffer for NumberOfCharsWritten
    mov dword[esp+16],0 ; lpReserved
    lea edx, [esp+20]
    mov [esp+12], edx; lpNumberOfCharsWritten
    mov edx, msg.end - msg
    mov [esp+8], edx; nNumberOfCharsToWrite
    lea edx, [msg]
    mov [esp+4], edx; lpBuffer
    mov [esp], eax; hConsoleOutput
    call _WriteConsoleA@20
    mov ecx, [esp]
    test ecx, ecx
    jnz .write_ok
    push dword -2
    call _ExitProcess@4
.write_ok:
    xor eax, eax
    leave
    ret