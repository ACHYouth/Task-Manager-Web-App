#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

// Function to encrypt the plaintext using Caesar's cipher
string caesar_cipher(string plaintext, int key)
{
    int length = strlen(plaintext);
    for (int i = 0; i < length; i++)
    {
        char c = plaintext[i];
        if (isalpha(c))
        {
            char base = isupper(c) ? 'A' : 'a';
            plaintext[i] = (c - base + key) % 26 + base;
        }
    }
    return plaintext;
}

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    int key = atoi(argv[1]);

    string plaintext = get_string("plaintext: ");
    string ciphertext = caesar_cipher(plaintext, key);

    printf("ciphertext: %s\n", ciphertext);
    return 0;
}
