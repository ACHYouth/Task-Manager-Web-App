#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <wchar.h>

void print_bulb(char *binary)
{
    for (int i = 0; i < 8; i++)
    {
        wchar_t bulb = (binary[i] == '1') ? L'💡' : L'⚫';
        wprintf(L"%lc ", bulb);
    }
    wprintf(L"\n");
}

void char_to_binary(char c, char *binary)
{
    for (int i = 7; i >= 0; i--)
    {
        binary[i] = (c & 1) + '0';
        c >>= 1;
    }
}

int main(void)
{
    string message = get_string("Enter your message: ");

    int length = strlen(message);
    char binary[8];

    for (int i = 0; i < length; i++)
    {
        char_to_binary(message[i], binary);
        print_bulb(binary);
    }

    return 0;
}
