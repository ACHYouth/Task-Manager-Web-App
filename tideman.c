#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define MAX_CANDIDATES 9

typedef struct
{
    int preferences[MAX_CANDIDATES];
    bool eliminated;
}
voter;

typedef struct
{
    string name;
    int votes;
}
candidate;

voter voters[MAX_CANDIDATES];
candidate candidates[MAX_CANDIDATES];
int candidate_count;
int voter_count;

bool vote(int voter, int rank, string name);
void tabulate(void);
bool is_tie(int max_votes);
void print_winner(void);
int get_index(string name);

int main(int argc, string argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s candidate1 candidate2 candidate3 ... candidate9\n", argv[0]);
        return 1;
    }

    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %d\n", MAX_CANDIDATES);
        return 2;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    voter_count = get_int("Number of voters: ");

    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %d: ", j + 1);
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }
        printf("\n");
    }

    tabulate();

    print_winner();

    return 0;
}

bool vote(int voter, int rank, string name)
{
    int index = get_index(name);
    if (index == -1)
    {
        return false;
    }

    voters[voter].preferences[rank] = index;
    return true;
}

void tabulate(void)
{
    for (int i = 0; i < voter_count; i++)
    {
        int j = 0;
        while (candidates[voters[i].preferences[j]].eliminated)
        {
            j++;
        }
        candidates[voters[i].preferences[j]].votes++;
    }
}

bool is_tie(int max_votes)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes != max_votes)
        {
            return false;
        }
    }
    return true;
}

void print_winner(void)
{
    while (true)
    {
        int max_votes = 0;

        for (int i = 0; i < candidate_count; i++)
        {
            if (!candidates[i].eliminated && candidates[i].votes > max_votes)
            {
                max_votes = candidates[i].votes;
            }
        }

        if (is_tie(max_votes))
        {
            break;
        }

        for (int i = 0; i < candidate_count; i++)
        {
            if (candidates[i].votes == max_votes)
            {
                candidates[i].eliminated = true;
            }
        }
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated)
        {
            printf("%s\n", candidates[i].name);
        }
    }
}

int get_index(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            return i;
        }
    }
    return -1;
}
