#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>



void win()
{
    printf("code flow successfully changed\n");
}

int main(int argc, char **argv)
{
	struct {
		char buffer[64];
		volatile int (*fp)();
    } s;

    s.fp = 0;

    gets(s.buffer);

    if(s.fp) {
        printf("calling function pointer, jumping to 0x%p\n", s.fp);
        s.fp();
    }
}