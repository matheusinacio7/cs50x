// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

bool insert_word(char *word);
bool insert_next(node *prev, char *word, int index);
void free_node(node *n);
bool check_linked_list(node *n, const char *word);
bool is_same_word_case_insensitive(char *w1, const char *w2);

int count_bucket_usage(node *n, int rolling_count);

const unsigned int N = 10000;

int dict_word_count = 0;

// Hash table
node *table;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int hash_i = hash(word);
    return check_linked_list(&table[hash_i], word);
}

bool check_linked_list(node *n, const char *word)
{
    if (is_same_word_case_insensitive(n->word, word))
    {
        return true;
    }

    if (n->next == NULL)
    {
        return false;
    }

    return check_linked_list(n->next, word);
}

bool is_same_word_case_insensitive(char *w1, const char *w2)
{
    if (strlen(w1) != strlen(w2))
    {
        return false;
    }

    for (int i = 0; i < strlen(w1); i++)
    {
        if (tolower(w1[i]) != tolower(w2[i]))
        {
            return false;
        }
    }

    return true;
}

// Hashes word to a number
// Some theoretical references:
// https://opendsa-server.cs.vt.edu/ODSA/Books/CS3/html/HashFuncExamp.html (and other pages)
// https://kottke.org/17/07/the-distribution-of-letters-in-english-words
unsigned int hash(const char *word)
{
    int wlen = strlen(word);

    __u_long sum = 0;
    for (int i = 0; i < wlen; i++)
    {
        sum += word[i] * word[i] * word[i];
    }

    char as_word[15];
    sprintf(as_word, "%lu", sum);
    int digit_count = strlen(as_word);

    int result;

    if (digit_count > 5)
    {
        int discarded_digit_count = digit_count - 5;
        int discarded_half = discarded_digit_count / 2;

        char result_str[6];
        result_str[5] = '\0';

        for (int i = 0; i < 5; i++)
        {
            result_str[i] = as_word[i + discarded_half];
        }

        result = atoi(result_str);
    }
    else
    {
        result = sum;
    }


    return result % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    table = calloc(N, sizeof(node));
    char c;
    FILE *dict = fopen(dictionary, "r");

    bool loaded = false;
    int index = 0;
    char word[LENGTH + 1];

    while (fread(&c, sizeof(char), 1, dict))
    {
        if (c != '\n')
        {
            word[index] = c;
            index++;
        }
        else
        {
            word[index] = '\0';
            loaded = insert_word(word);

            // if a word could not be loaded, break
            if (!loaded)
            {
                break;
            }

            index = 0;
            dict_word_count++;
        }
    }

    fclose(dict);
    return loaded;
}

bool insert_word(char *word)
{
    int hash_index = hash(word);
    bool inserted = false;

    if (table[hash_index].word[0] == '\000')
    {
        strcpy(table[hash_index].word, word);
        return true;
    }
    else
    {
        inserted = insert_next(&table[hash_index], word, hash_index);
        return inserted;
    }

    return inserted;
}

bool insert_next(node *prev, char *word, int index)
{
    node *next = prev->next;
    if (next == NULL)
    {
        node *new_node = calloc(1, sizeof(node));
        if (!new_node)
        {
            return false;
        }

        strcpy(new_node->word, word);
        prev->next = new_node;
        return true;
    }
    else
    {
        return insert_next(next, word, index);
    }
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dict_word_count;
}

void benchmark(void)
{
    printf("BUCKETS: %i\n", N);
    int unused_buckets = 0;
    int most_used_buckets[3][2];
    int least_used_buckets[3][2];

    for (int i = 0; i < 3; i++) {
        most_used_buckets[i][0] = 99;
        most_used_buckets[i][1] = 0;

        least_used_buckets[i][0] = 99;
        least_used_buckets[i][1] = __INT_MAX__;
    }

    for (int b = 0; b < N; b++)
    {
        if (table[b].word[0] == '\000')
        {
            unused_buckets++;
            continue;
        }

        int bucket_count = count_bucket_usage(&table[b], 0);
        for (int i = 0; i < 3; i++)
        {
            if (bucket_count > most_used_buckets[i][1])
            {
                int swap[2];
                swap[0] = most_used_buckets[i][0];
                swap[1] = most_used_buckets[i][1];

                most_used_buckets[i][0] = b;
                most_used_buckets[i][1] = bucket_count;
                if (i != 2)
                {
                    most_used_buckets[i + 1][0] = swap[0];
                    most_used_buckets[i + 1][1] = swap[1];
                }
                break;
            }
        }

        for (int i = 0; i < 3; i++)
        {
            if (bucket_count < least_used_buckets[i][1])
            {
                int swap[2];
                swap[0] = least_used_buckets[i][0];
                swap[1] = least_used_buckets[i][1];

                least_used_buckets[i][0] = b;
                least_used_buckets[i][1] = bucket_count;
                if (i != 2)
                {
                    least_used_buckets[i + 1][0] = swap[0];
                    least_used_buckets[i + 1][1] = swap[1];
                }
                break;
            }
        }
    }

    printf("UNUSED BUCKETS: %i\n", unused_buckets);
    printf("MOST USED BUCKETS:\n");
    for (int i = 0; i < 3; i++)
    {
        printf("    bucket %i:  used %i times\n", most_used_buckets[i][0], most_used_buckets[i][1]);
    }
    printf("LEAST USED BUCKETS:\n");
    for (int i = 0; i < 3; i++)
    {
        printf("    bucket %i:  used %i times\n", least_used_buckets[i][0], least_used_buckets[i][1]);
    }
}

int count_bucket_usage(node *n, int rolling_count)
{
    if (n == NULL)
    {
        return rolling_count;
    }

    return count_bucket_usage(n->next, rolling_count + 1);
}


// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        free_node(table[i].next);
    }

    free(table);
    return true;
}

void free_node(node *n)
{
    if (n == NULL)
    {
        return;
    }

    free_node(n->next);
    free(n);
}
