#include <stdio.h>

char buffer[4096]; // global variable without assigned value -> filled with zeros

int main(){
    fgets(buffer, sizeof(buffer), stdin);
    int count = 0;
    char x;
cycle_start:
    x = buffer[count];
    if(x == 0) goto cycle_end;
    if(x == '\n') goto cycle_end;
    count = count+1;
    goto cycle_start;
cycle_end:
    printf("%d", count);
}