#include <stdio.h>

int main(){
    int count;
    long long int result =0;
    scanf("%d", &count);
    while(--count >= 0){
        long long x;
        scanf("%lld", &x);
        result += x;
    }
    printf("%lld", result) ;
}