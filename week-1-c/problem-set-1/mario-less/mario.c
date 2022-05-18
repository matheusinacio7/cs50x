#include <cs50.h>
#include <stdio.h>

int get_pyramid_height(void);
void print_pyramid(int height);

int main(void) 
{
    const int pyramid_height = get_pyramid_height();
    print_pyramid(pyramid_height);
}

int get_pyramid_height(void)
{
    int pyramid_height;
    do
    {
        pyramid_height = get_int("Height: ");
    }
    while (pyramid_height < 1 || pyramid_height > 8);

    return pyramid_height;
}

void print_pyramid(int height)
{
    const char block = '#';
    const char space = ' ';
    for (int line = 0; line < height; line++)
    {
        const int blocks = line + 1;
        const int spaces = height - blocks;
        for (int column = 0; column < spaces; column++)
        {
            printf("%c", space);
        }
        for (int column = 0; column < blocks; column++)
        {
            printf("%c", block);
        }
        printf("\n");
    }
}
