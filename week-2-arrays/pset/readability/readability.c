#include <cs50.h>
#include <stdio.h>
#include <string.h>

int get_coleman_liau_index(float L, float S);
int get_word_count(string text);
void split_string(string *target, string source, char separator);
int get_split_string_count(string text, char separator);
float get_average_letters_per_hundred_words(string text, int word_count);
float get_average_sentences_per_hundred_words(string text, int word_count);

int main(void) 
{
    printf("Colemn Liau Index Grade Calculator!\n");
    string text = get_string("Text: ");
    int word_count = get_word_count(text);
    // float L = get_average_letters_per_hundred_words(text, word_count);
    // float S = get_average_sentences_per_hundred_words(text, word_count);
    // int index = get_coleman_liau_index(L, S);
    // printf("Grade %i\n", index);
}

// Where L is the average of letters per 100 words in the text, and S is the average of sentences per 100 words in the text
int get_coleman_liau_index(float L, float S)
{
    return (int) (0.0588 * L - 0.296 * S - 15.8);
}

int get_word_count(string text)
{
    return get_split_string_count(text, ' ');
}

int get_split_string_count(string text, char separator)
{
    int count = 1;

    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == separator)
        {
            count++;
        }
    }

    return count;
}
