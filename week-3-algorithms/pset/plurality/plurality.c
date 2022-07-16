#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(void)
{
    // Check for invalid usage
    int argc = 4;
    string argv[] = { "plurality", "Alice", "Bob", "Charlie" };

    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes += 1;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    candidate current_winners[MAX] = {{ .name = "", .votes = 0 }};
    int winner_count = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > current_winners[0].votes)
        {
            current_winners[0] = candidates[i];
            winner_count = 1;
        }
        else if (candidates[i].votes == current_winners[0].votes)
        {
            current_winners[winner_count] = candidates[i];
            winner_count += 1;
        }
    }

    string current_winner_name = "";
    int i = 0;
    do
    {
        current_winner_name = current_winners[i].name;
        printf("%s\n", current_winner_name);
        i += 1;
    }
    while (strcmp(current_winner_name, "") != 0 && i < winner_count);

    return;
}