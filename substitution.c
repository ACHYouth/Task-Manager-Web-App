#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

bool is_valid_key(string key)
{
    if (strlen(key) != 26)
    {
        return false;
    }

    int occurrences[26] = {0};

    for (int i = 0; i < 26; i++)
    {
        if (!isalpha(key[i]))
        {
            return false;
        }

        int index = tolower(key[i]) - 'a';
        if (occurrences[index] == 1)
        {
            return false;
        }
        occurrences[index]++;
    }

    return true;
}

string encrypt(string plaintext, string key)
{
    string ciphertext = plaintext;

    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        char c = plaintext[i];

        if (isalpha(c))
        {
            bool is_uppercase = isupper(c);
            int index = tolower(c) - 'a';
            c = key[index];

            if (is_uppercase)
            {
                c = toupper(c);
            }
        }

        ciphertext[i] = c;
    }

    return ciphertext;
}

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }

    string key = argv[1];

    if (!is_valid_key(key))
    {
        printf("Key must contain 26 characters, each exactly once.\n");
        return 1;
    }

    string plaintext = get_string("plaintext: ");

    string ciphertext = encrypt(plaintext, key);

    printf("ciphertext: %s\n", ciphertext);

    return 0;
}
