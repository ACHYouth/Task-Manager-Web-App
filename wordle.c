#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cs50.h>
#include <string.h>
#include <stdbool.h>

string generate_word()
{
    string word = "ABCDE";
    for (int i = 0; i < 5; i++)
    {
        int j = i + rand() % (5 - i);
        char temp = word[i];
        word[i] = word[j];
        word[j] = temp;
    }
    return word;
}

void check_guess(string secret_word, string guess)
{
    int bulls = 0, cows = 0;
    bool used[5] = {false};

    for (int i = 0; i < 5; i++)
    {
        if (guess[i] == secret_word[i])
        {
            bulls++;
            used[i] = true;
        }
    }

    for (int i = 0; i < 5; i++)
    {
        if (!used[i])
        {
            for (int j = 0; j < 5; j++)
            {
                if (!used[j] && guess[i] == secret_word[j])
                {
                    cows++;
                    used[j] = true;
                    break;
                }
            }
        }
    }

    printf("Guess: %s   Bulls: %d   Cows: %d\n", guess, bulls, cows);
}

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <number of tries>\n", argv[0]);
        return 1;
    }

    int max_tries = atoi(argv[1]);
    string secret_word = generate_word();
    string guess;

    printf("This is WORDLE50\n");
    printf("You have %d tries to guess the 5-letter word I'm thinking of\n", max_tries);

    for (int i = 0; i < max_tries; i++)
    {
        guess = get_string("Input a 5-letter word: ");
        if (strlen(guess) != 5)
        {
            printf("Please input a 5-letter word.\n");
            continue;
        }

        if (strcmp(secret_word, guess) == 0)
        {
            printf("You won!\n");
            return 0;
        }

        check_guess(secret_word, guess);
    }

    printf("You lost! The word was %s.\n", secret_word);
    return 0;
}
