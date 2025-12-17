#include <stdio.h>

__attribute__((naked))
void toggle_trap_flag(){
    asm(
    "pushf\n\t"
    "mov ax, [rsp]\n\t"
    "xor ax, 0x100\n\t"
    "mov [rsp], ax\n\t"
    "popf\n\t"
    );

    asm(
            "ret\n\t" //<-  #DB exception
    );

}

volatile int target = 0;

int main(){
    ++target;
    ++target;
    ++target;
    toggle_trap_flag();
    ++target; //<-  #DB exception x 3 (increment compiled as MOV-ADD-MOV)
    ++target; //<-  #DB exception x 3
    ++target; //<-  #DB exception x 3
    toggle_trap_flag(); //<-  #DB exception x 6
    ++target;
    ++target;
    ++target;
    printf("%d", target);
}