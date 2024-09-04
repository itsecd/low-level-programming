#include <stdio.h>

char buffer[4096];

int main(){
    fgets(buffer, sizeof(buffer), stdin);
    int count = 0;
    while(buffer[count] && buffer[count] != '\n')
        ++count;
    printf("%d", count);
}