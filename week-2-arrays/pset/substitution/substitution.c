#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_usage_reminder(void);
void extract_cipher(string raw_cipher, char lower_case_cipher[26], char upper_case_cipher[26]);
void validate_cipher(string raw_cipher);
void encrypt(string plain, char lower_case_cipher[26], char upper_case_cipher[26]);

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

    char upper_case_cipher[26] = { 'A' };
    char lower_case_cipher[26] = { 'a' };
    extract_cipher(raw_cipher, lower_case_cipher, upper_case_cipher);

    string text = get_string("plaintext:  ");
    encrypt(text, lower_case_cipher, upper_case_cipher);
    printf("ciphertext: %s\n", text);
    return 0;
}

void print_usage_reminder(void)
{
    printf("Usage: ./substitution cipher\n");
    printf("  cipher: 26 letters that letters a-z will be substituted for.\n");
    printf("     Case insensitive.\n");
    printf("     Must contain exactly one of each letter.\n");
}

void extract_cipher(string raw_cipher, char lower_case_cipher[26], char upper_case_cipher[26])
{
    for (int i = 0; i < strlen(raw_cipher); i++)
    {
        char raw_cipher_char = raw_cipher[i];
        if (!isalpha(raw_cipher_char))
        {
            print_usage_reminder();
            exit(1);
        }
        lower_case_cipher[i] = tolower(raw_cipher_char);
        upper_case_cipher[i] = toupper(raw_cipher_char);
    }
    validate_cipher(lower_case_cipher);
}

void validate_cipher(char lower_case_cipher[26])
{
    char sorted_cipher[26] = { 'a' };
    for (int i = 0; i < 26; i++)
    {
        sorted_cipher[i] = lower_case_cipher[i];
    }

    // bubble sort
    for (int i = 0; i < 26; i++)
    {
        for (int j = i + 1; j < 26; j++)
        {
            if (sorted_cipher[j] < sorted_cipher[i])
            {
                char swap = sorted_cipher[j];
                sorted_cipher[j] = sorted_cipher[i];
                sorted_cipher[i] = swap;
            }
        }
    }

    for (int i = 0; i < 25; i++)
    {
        if (sorted_cipher[i] == sorted_cipher[i + 1])
        {
            print_usage_reminder();
            exit(1);
        }
    }
}

void encrypt(string text, char lower_case_cipher[26], char upper_case_cipher[26])
{
    for (int i = 0; i < strlen(text); i++)
    {
        char plain_char = text[i];
        if (isupper(plain_char))
        {
            int index = (int) plain_char - 65;
            text[i] = upper_case_cipher[index];
        }
        else if (islower(plain_char))
        {
            int index = (int) plain_char - 97;
            text[i] = lower_case_cipher[index];
        }
        else
        {
            text[i] = plain_char;
        }
    }
}
