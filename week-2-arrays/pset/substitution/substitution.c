#include <cs50.h>
#include <stdio.h>
#include <string.h>

void print_usage_reminder(void);

int main(int argc, string argv[]) 
{
    if (argc != 2)
    {
        print_usage_reminder();
        return 1;
    }
    string raw_cipher = argv[1];

    if (strlen(argv[1]) != 26)
    {
        print_usage_reminder();
        return 1;
    }
}

void print_usage_reminder(void)
{
    printf("Usage: ./substitution cipher\n");
    printf("  cipher: 26 letters that letters a-z will be substituted for. Case insensitive.\n");
}
