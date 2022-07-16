#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void print_usage_reminder(void);
int string_to_int(string number);
int char_to_int(char number);
void rotate_phrase(string phrase, int key);
char rotate_letter(char letter, int key);

int main(int argc, string argv[]) 
{
    if (argc != 2)
    {
        print_usage_reminder();
        return 1;
    }

    int key = string_to_int(argv[1]);
    string text = get_string("plaintext:  ");
    rotate_phrase(text, key);
    printf("ciphertext: %s\n", text);
}

void print_usage_reminder(void)
{
    printf("Usage: ./caesar key\n");
}

void rotate_phrase(string phrase, int key)
{
    for (int i = 0; i < strlen(phrase); i++)
    {
        phrase[i] = rotate_letter(phrase[i], key);
    }
}

char rotate_letter(char letter, int key)
{
    int code = (int) letter;
    int upper_case_range[] = { 65, 90 };
    int lower_case_range[] = { 97, 122 };

    if (code >= upper_case_range[0] && code <= upper_case_range[1])
    {
        int new_code = code + key % 26;
        return new_code <= upper_case_range[1] ? (char) new_code : (char) new_code - 26;
    }
    else if (code >= lower_case_range[0] && code <= lower_case_range[1])
    {
        int new_code = code + key % 26;
        return new_code <= lower_case_range[1] ? (char) new_code : (char) new_code - 26;
    }
    else
    {
        return letter;
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
