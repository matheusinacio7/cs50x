#include <cs50.h>
#include <stdio.h>

int get_coleman_liau_index(float L, float S);

int main(void) 
{
    int index = get_coleman_liau_index(464.29, 28.57);
}

// Where L is the average of letters per 100 words in the text, and S is the average of sentences per 100 words in the text
int get_coleman_liau_index(float L, float S)
{
    return (int) (0.0588 * L - 0.296 * S - 15.8);
}
