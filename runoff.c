#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define MAX_VOTERS 100
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

voter voters[MAX_VOTERS];
candidate candidates[MAX_CANDIDATES];
int candidate_count;
int voter_count;

bool vote(int voter, string name);
bool is_tie(int min_votes);
void eliminate(int min_votes);
bool print_winner(void);
void runoff(void);
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
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %d\n", MAX_VOTERS);
        return 3;
    }

    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %d: ", j + 1);
            if (!vote(i, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }
        printf("\n");
    }

    runoff();

    return 0;
}

bool vote(int voter, string name)
{
    int index = get_index(name);
    if (index == -1)
    {
        return false;
    }

    voters[voter].preferences[index] = 1;
    return true;
}

bool is_tie(int min_votes)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > 0 && candidates[i].votes != min_votes)
        {
            return false;
        }
    }
    return true;
}

void eliminate(int min_votes)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min_votes)
        {
            candidates[i].eliminated = true;
        }
    }
}

bool print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > voter_count / 2)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

void runoff(void)
{
    while (true)
    {
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }

        for (int i = 0; i < voter_count; i++)
        {
            for (int j = 0; j < candidate_count; j++)
            {
                if (!candidates[j].eliminated)
                {
                    candidates[voters[i].preferences[j]].votes++;
                    break;
                }
            }
        }

        int min_votes = voter_count;
        for (int i = 0; i < candidate_count; i++)
        {
            if (!candidates[i].eliminated && candidates[i].votes < min_votes)
            {
                min_votes = candidates[i].votes;
            }
        }

        if (is_tie(min_votes))
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        eliminate(min_votes);
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
