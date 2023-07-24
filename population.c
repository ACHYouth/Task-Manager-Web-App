#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int start_size, end_size;
    int years = 0;

    // Prompt the user for the starting and ending population sizes
    do
    {
        start_size = get_int("Start size: ");
    } while (start_size < 9); 

    do
    {
        end_size = get_int("End size: ");
    } while (end_size < start_size);


    while (start_size < end_size)
    {
        int born = start_size / 3;
        int dead = start_size / 4;
        int net_growth = born - dead;

        start_size += net_growth;
        years++;
    }


    printf("Years: %d\n", years);

    return 0;
}
