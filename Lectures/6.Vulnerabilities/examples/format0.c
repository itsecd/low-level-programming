#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void vuln(char *string)
{
	struct {
		char buffer[64];
		volatile int target;
	} s;

    s.target = 0;

    sprintf(s.buffer, string);

    if(s.target == 0xdeadbeef) {
        printf("you have hit the target correctly :)\n");
    }
}

int main(int argc, char **argv)
{
    vuln(argv[1]);
}