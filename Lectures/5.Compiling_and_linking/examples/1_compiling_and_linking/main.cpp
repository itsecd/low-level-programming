#include <stdio.h>
extern unsigned int a;
void read_a();

unsigned int read_b();

static void say_bye(unsigned int x)
{
    while ( x-- > 0)
    {
        puts("Bye!");
    }
}

int y;

int main()
{
    read_a();
    say_bye(a + read_b());
}