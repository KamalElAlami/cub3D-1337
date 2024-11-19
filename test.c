#include <libc.h>

void f()
{
    system("leaks a.out");
}
int main()
{
    char *line;
    line = malloc(1);

    atexit(f);
    line[0] = 65;
    printf("%c\n", line[0]);
}