#include <stdio.h>

char buffer[65]; 

void radix_print(unsigned long long x, unsigned int radix){
	buffer[64] = 0; // end of line
    int count = 63;
    do{
        unsigned int digit = x % radix;
        x /= radix;
        if (digit < 10)
            digit = '0'+digit;
        else
            digit = 'a'+digit-10;
        buffer[count--] = digit;
    }while(x > 0);
    puts(buffer+count+1);
}

int main(){

    unsigned long long x;
    scanf("%llu", &x);
    radix_print(x, 2);
    radix_print(x, 8);
    radix_print(x, 10);
    radix_print(x, 16);
    radix_print(x, 32);
}
