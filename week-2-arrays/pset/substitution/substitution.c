#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_usage_reminder(void);
void extract_cipher(string raw_cipher, char lower_case_cipher[26], char upper_case_cipher[26]);

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

    // string raw_cipher = "JTREKYAVOGDXPSNCUIZLFBMWHQ";

    char upper_case_cipher[26] = { 'A' };
    char lower_case_cipher[26] = { 'a' };
    extract_cipher(raw_cipher, lower_case_cipher, upper_case_cipher);

    // char whatever = 'k';
}

void print_usage_reminder(void)
{
    printf("Usage: ./substitution cipher\n");
    printf("  cipher: 26 letters that letters a-z will be substituted for. Case insensitive.\n");
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
}
