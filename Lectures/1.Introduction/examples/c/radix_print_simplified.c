#include <stdio.h>

char buffer[65];

void radix_print(unsigned long long x, unsigned int radix){
	buffer[64] = 0; // end of line
    int count = 63;
    unsigned int digit;

cycle_start:
        digit = x % radix;
        x /= radix;

        if (digit >= 10) goto else_label;

        digit += '0';
        goto if_end;

else_label:
        digit += 'a';
        digit -= 10;

if_end:
        buffer[count] = digit;
        count-=1;
        if(x > 0) goto cycle_start;

    char* address = &buffer[count+1];
    puts(address);
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
