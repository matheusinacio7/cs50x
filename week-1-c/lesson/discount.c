#include <stdio.h>
#include <cs50.h>

float discount(float price, int percentage_off);

int main(void)
{
    const float regular_price = get_float("Regular price: ");
    const int percentage_off = get_int("Percentage off: ");
    printf("Discounted price: %.2f\n", discount(regular_price, percentage_off));
}

float discount(float price, int percentage_off)
{
    return price * (100 - percentage_off) / 100;
}
