#include <stdio.h>

int main(void)
{
    char *s = "HI!";
    printf("%p -> %i\n", &s[0], *&s[0]);
    printf("%p -> %i\n", &s[1], *&s[1]);
    printf("%p -> %i\n", &s[2], *&s[2]);
    printf("%p -> %i\n", &s[3], *&s[3]);
    printf("%p -> %i\n", &s[4], *&s[4]);
    printf("%p -> %i\n", &s[5], *&s[5]);
    printf("%p -> %i\n", &s[6], *&s[6]);
}
