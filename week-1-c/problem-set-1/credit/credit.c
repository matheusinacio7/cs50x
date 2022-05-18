#include <cs50.h>
#include <stdio.h>
#include <string.h>

string get_card_number(char* card_number);
string get_card_brand(string card_number);

int main(void) 
{
    char card_number[17];
    get_card_number(card_number);

    const string card_brand = get_card_brand(card_number);
    printf("%s\n", card_brand);
}

string get_card_number(char* card_number)
{
    const long long_card_number = get_long("What's the credit card number? ");
    sprintf(card_number, "%li", long_card_number);
    return card_number;
}

string get_card_brand(string card_number)
{
    // Check if card is VISA: 13 or 16 digits, starting with 4
    const char first_digit = card_number[0];
    const bool has_visa_number_count = strlen(card_number) == 13 || strlen(card_number) == 16;
    if (has_visa_number_count && first_digit == '4')
    {
        return "VISA";
    }

    // other cards need two digits
    char first_two_digits[2];
    memcpy(first_two_digits, card_number, 2);

    // check if card is American Express: starts with 34 or 37 and 15 digits
    const bool has_amex_first_digits = strcmp(first_two_digits, "34") == 0
        || strcmp(first_two_digits, "37") == 0;
    if (has_amex_first_digits && strlen(card_number) == 15)
    {
        return "AMEX";
    }

    // check if card is Mastercard: starts with 51 through 55 and 16 digits
    const bool has_mastercard_first_digits = strcmp(first_two_digits, "51") == 0
        || strcmp(first_two_digits, "52") == 0
        || strcmp(first_two_digits, "53") == 0
        || strcmp(first_two_digits, "54") == 0
        || strcmp(first_two_digits, "55") == 0;
    
    if (has_mastercard_first_digits && strlen(card_number) == 16)
    {
        return "MASTER";
    }

    return "INVALID";
}
