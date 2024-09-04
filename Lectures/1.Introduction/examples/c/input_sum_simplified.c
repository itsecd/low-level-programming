#include <stdio.h>

int main(){
    int count;
    long long int result =0;
    scanf("%d", &count);
cycle_start:
    --count;
    if(count < 0) goto cycle_end;
    long long x;
    scanf("%lld", &x);
    result += x;
    goto cycle_start;
cycle_end:
    printf("%lld", result) ;
}