#include <stdio.h>
#include <stdlib.h>

void print_usage_reminder(void);
 
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        print_usage_reminder();
        return 2;
    }

    char *filename = argv[1];
}

void print_usage_reminder(void)
{
    printf("Usage: recover FILE_PATH\n");
}
