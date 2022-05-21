#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);
void print_winner(int score1, int score2);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    print_winner(score1, score2);
    printf("\n");
}

int compute_score(string word)
{
    int codeForA = 65;
    int sum = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        int letter_index = (int) toupper(word[i]) - codeForA;
        int letter_score = letter_index > 0 && letter_index < 26 ? POINTS[letter_index] : 0;
        sum += letter_score;
    }
    return sum;
}

void print_winner(int score1, int score2)
{
    if (score1 > score2)
    {
        printf("Player 1 wins!");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!");
    }
    else
    {
        printf("Tie!");
    }
}
