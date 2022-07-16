#include <stdio.h>
#include <cs50.h>

int main(void)
{
    const string first_name = get_string("What's your first name? ");
    printf("hello, %s\n", first_name);
}
