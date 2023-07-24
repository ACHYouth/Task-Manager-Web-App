#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long long card_number;

    card_number = get_long("Number: ");

    // to calc sum of digits
    int sum = 0;
    int digit_count = 0;

    while (card_number > 0)
    {
        int digit = card_number % 10;
        card_number /= 10;
        digit_count++;

        if (digit_count % 2 == 0)
        {
            digit *= 2;

            if (digit >= 10)
            {
                sum += digit / 10 + digit % 10;
            }
            else
            {
                sum += digit;
            }
        }
        else
        {
            sum += digit;
        }
    }

    // to check card type and validity
    if (sum % 10 == 0)
    {
        // to find card type
        int first_two_digits = card_number;
        while (first_two_digits >= 100)
        {
            first_two_digits /= 10;
        }

        if ((digit_count == 15 && (first_two_digits == 34 || first_two_digits == 37)))
        {
            printf("AMEX\n");
        }
        else if (digit_count == 16 && (first_two_digits >= 51 && first_two_digits <= 55))
        {
            printf("MASTERCARD\n");
        }
        else if ((digit_count == 13 || digit_count == 16) && (first_two_digits / 10 == 4))
        {
            printf("VISA\n");
        }
        
    }
    else
    {
        printf("INVALID\n");
    }

}