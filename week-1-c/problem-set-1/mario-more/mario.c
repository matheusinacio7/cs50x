#include <cs50.h>
#include <stdio.h>

int get_pyramid_height(void);
void print_pyramid(int height);
void print_bricks(int height, int line);
void print_spaces(int height, int line);

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
    for (int line = 0; line < height; line++)
    {
        const char space = ' ';
        print_spaces(height, line);
        print_bricks(height, line);
        printf("%c%c", space, space);
        print_bricks(height, line);
        printf("\n");
    }
}

void print_spaces(int height, int line)
{
    const char space = ' ';
    const int blocks = line + 1;
    const int spaces = height - blocks;
    for (int column = 0; column < spaces; column++)
    {
        printf("%c", space);
    }
}

void print_bricks(int height, int line)
{
    const char block = '#';
    const int blocks = line + 1;
    for (int column = 0; column < blocks; column++)
    {
        printf("%c", block);
    }
}
