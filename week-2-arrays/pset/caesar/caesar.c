#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void print_usage_reminder(void);
int string_to_int(string number);
int char_to_int(char number);

int main(int argc, string argv[]) 
{
    int my_int = string_to_int("12489");

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

int string_to_int(string number)
{
    int rolling_number = 0;
    int last_index = strlen(number) - 1;
    for (int n = 0; n <= last_index; n++)
    {
        int digit = char_to_int(number[last_index - n]);
        rolling_number += digit * pow(10, n);
    }
    return rolling_number;
}

int char_to_int(char number)
{
    int code = (int) number;
    if (code > 57 || code < 48)
    {
        print_usage_reminder();
        exit(1);
    }

    return code - 48;
}
