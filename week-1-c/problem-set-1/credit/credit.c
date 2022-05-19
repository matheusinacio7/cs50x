#include <cs50.h>
#include <stdio.h>
#include <string.h>

string get_card_number(char* card_number);
string get_card_brand(string card_number);
bool get_card_number_is_valid(string card_number);
int get_sum_of_digits(int n);

int main(void) 
{
    char card_number[25] = {0};
    get_card_number(card_number);

    const string card_brand = get_card_brand(card_number);
    if (card_brand == "INVALID")
    {
        printf("%s\n", card_brand);
        return 0;
    }

    bool has_valid_numbers = get_card_number_is_valid(card_number);
    if (has_valid_numbers)
    {
        printf("%s\n", card_brand);
        return 0;
    } else {
        printf("INVALID\n");
        return 0;
    }
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
    char first_two_digits[4] = {0};
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
        return "MASTERCARD";
    }

    return "INVALID";
}

bool get_card_number_is_valid(string card_number)
{
    int doubled_digits_sum = 0;
    for (int i = strlen(card_number) - 2; i > -1; i -= 2)
    {
        int current_digit = (int) card_number[i] - 48;
        int doubled_digit = current_digit * 2;
        int sum_of_digits_doubled = get_sum_of_digits(doubled_digit);
        doubled_digits_sum += sum_of_digits_doubled;
    }

    int not_doubled_digits_sum = 0;

    for (int i = strlen(card_number) - 1; i > -1; i -= 2)
    {
        int current_digit = (int) card_number[i] - 48;
        not_doubled_digits_sum += current_digit;
    }

    int sum = doubled_digits_sum + not_doubled_digits_sum;
    if (sum % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int get_sum_of_digits(int n)
{
    char buffer[2] = {0};
    sprintf(buffer, "%i", n);
    int sum = 0;
    for (int i = 0; i < strlen(buffer); i++)
    {
        sum += (int) buffer[i] - 48;
    }
    return sum;
}
