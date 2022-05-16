#include <stdio.h>
#include <cs50.h>

void print_brick(int size);

int main(void)
{
    int brick_size;
    do
    {
        brick_size = get_int("Brick size: ");
    } while (brick_size < 0);

    print_brick(brick_size);
}

void print_brick(int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int i = 0; i < size; i++)
        {
            printf("#");
        }
        printf("\n");
    }
}
