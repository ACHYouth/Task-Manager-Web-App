#include <stdio.h>
#include <cs50.h>
#include <ctype.h>

int get_scrabble_score(string word)
{
    int score = 0;
    int letter_values[26] = {
        1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10,
        1, 1, 1, 1, 4, 4, 8, 4, 10
    };

    for (int i = 0; word[i] != '\0'; i++)
    {
        char letter = toupper(word[i]);

        if (letter >= 'A' && letter <= 'Z')
        {
            score += letter_values[letter - 'A'];
        }
    }

    return score;
}

int main(void)
{
    string player1, player2;
    int score1, score2;

    player1 = get_string("Player 1: ");
    player2 = get_string("Player 2: ");

    score1 = get_scrabble_score(player1);
    score2 = get_scrabble_score(player2);

    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }

    return 0;
}
