#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int get_coleman_liau_index(float L, float S);
int get_word_count(string text);
int get_letter_count(string text);
int get_split_string_count(string text, char *separators, int separators_size);
float get_average_letters_per_hundred_words(string text, int word_count);
float get_average_sentences_per_hundred_words(string text, int word_count);

int main(void) 
{
    printf("Colemn Liau Index Grade Calculator!\n");
    string text = get_string("Text: ");
    int word_count = get_word_count(text);
    float L = get_average_letters_per_hundred_words(text, word_count);
    float S = get_average_sentences_per_hundred_words(text, word_count);
    int index = get_coleman_liau_index(L, S);
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
    return 0;
}

// Where L is the average of letters per 100 words in the text, and S is the average of sentences per 100 words in the text
int get_coleman_liau_index(float L, float S)
{
    return round(0.0588 * L - 0.296 * S - 15.8);
}

int get_word_count(string text)
{
    return get_split_string_count(text, (char[]) {' '}, 1) + 1;
}

int get_split_string_count(string text, char *separators, int separators_size)
{
    int count = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == text[i - 1])
        {
            continue;
        }

        for (int j = 0; j < separators_size; j++)
        {
            if (text[i] == separators[j])
            {
                count++;
            }
        }
    }

    return count;
}

int get_letter_count(string text)
{
    int count = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        char current_as_upper = toupper(text[i]);
        int current_code = (int) current_as_upper;
        if (current_code >= 65 && current_code <= 90)
        {
            count += 1;
        }
    }

    return count;
}

float get_average_letters_per_hundred_words(string text, int word_count)
{
    int letter_count = get_letter_count(text);
    return (float) letter_count / word_count * 100;
}

float get_average_sentences_per_hundred_words(string text, int word_count)
{
    char separators[] = {'!', '.', '?'};
    int sentence_count = get_split_string_count(text, separators, 3);
    return (float) sentence_count / word_count * 100;
}
