#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long long card_number;

    card_number = get_long("Number: ");

    // to create array
    int digits[16];
    int digit_count = 0;

    // to extract digits from array
    while (card_number > 0)
    {
        digits[digit_count] = card_number % 10;
        card_number /= 10;
        digit_count++;
    }

    // to apply luhn's algorithm
    int sum = 0;
    int even_sum = 0;
    int odd_sum = 0;

    for (int i = 0; i < digit_count; i++)
    {
        if (i % 2 == 0)
        {
            odd_sum += digits[i];
        }
        else
        {
            int even_digit = digits[i] * 2;
            even_sum += even_digit % 10 + even_digit / 10;
        }
    }

    sum = even_sum + odd_sum;

    // to check card type and validity
    if (sum % 10 == 0)
    {
        // to check card type
        int first_two_digits = digits[digit_count - 1] * 10 + digits[digit_count - 2];

        if (digit_count == 15 && (first_two_digits == 34 || first_two_digits == 37))
        {
            printf("AMEX\n");
        }
        else if (digit_count == 16 && (first_two_digits >= 51 && first_two_digits <= 55))
        {
            printf("MASTERCARD\n");
        }
        else if ((digit_count == 13 || digit_count == 16) && (digits[digit_count - 1] == 4))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }

}