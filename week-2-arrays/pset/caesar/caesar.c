#include <cs50.h>
#include <stdio.h>

void print_usage_reminder(void);

int main(int argc, string argv[]) 
{
    if (argc != 2)
    {
        print_usage_reminder();
        return 1;
    }
}

void print_usage_reminder(void)
{
    printf("Usage: ./caesar key\n");
}
