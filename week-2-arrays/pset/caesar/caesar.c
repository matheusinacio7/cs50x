#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void print_usage_reminder(void);
int string_to_int(string number);
int char_to_int(char number);
char rotate_letter(char letter, int key);

int main(int argc, string argv[]) 
{
    char rotated = rotate_letter('B', 5);

    if (argc != 2)
    {
        print_usage_reminder();
        return 1;
    }

    int key = string_to_int(argv[0]);
}

void print_usage_reminder(void)
{
    printf("Usage: ./caesar key\n");
}

char rotate_letter(char letter, int key)
{
    int code = (int) letter;
    int upper_case_range[] = { 65, 90 };
    int lower_case_range[] = { 97, 122 };

    if (code < upper_case_range[0] || code > lower_case_range[1])
    {
        return letter;
    }
    else if (code > upper_case_range[1] && code < lower_case_range[0])
    {
        return letter;
    }
    else
    {
        int new_code = code + key % 26;
        return (char) new_code;
    }
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
