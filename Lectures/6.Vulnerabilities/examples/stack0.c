#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    /* Переменные заключены в структуру, чтобы компилятор не изменил их порядок
     * В оригинале это были 2 отдельные переменные. На логику работы программы изменение не влияет.
     * */
	struct {
		char buffer[64];
		volatile int modified;
    }s;

    s.modified = 0;
    gets(s.buffer);

    if(s.modified != 0) {
        printf("you have changed the 'modified' variable\n");
    } else {
        printf("Try again?\n");
    }
}