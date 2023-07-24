#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int get_coleman_liau_index(string text)
{
    int letters = 0;
    int words = 0;
    int sentences = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
        else if (isspace(text[i]))
        {
            if (i > 0 && !isspace(text[i - 1]))
            {
                words++;
            }
        }
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }

    if (strlen(text) > 0 && !isspace(text[strlen(text) - 1]))
    {
        words++;
    }

    float L = (float)letters / words * 100;
    float S = (float)sentences / words * 100;

    return (int)(0.0588 * L - 0.296 * S - 15.8);
}

int main(void)
{
    string text;

    text = get_string("Text: ");

    int index = get_coleman_liau_index(text);

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
        printf("Grade %d\n", index);
    }

    return 0;
}
