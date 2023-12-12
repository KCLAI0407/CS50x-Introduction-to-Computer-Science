#include <cs50.h>
#include <stdio.h>

long power(int n, int m);
int check_digit(long number, int count);
int main(void)
{
    long number;
    // prompt for input
    number = get_long("Number: ");
    // cal the checksum
    int count = 0;
    int sum = 0;
    int digit;
    for (long i = number; i > 0; i = i / 10)
    {
        digit = i % 10;
        count++;
        if (count % 2 == 0)
        {
            int double_digit = 2 * digit;
            if ((double_digit / 10) != 0)
            {
                sum += double_digit / 10;
                sum += double_digit % 10;
            }
            else
            {
                sum += double_digit;
            }
        }
        else
        {
            sum += digit;
        }
    }
    // printf("%i\n",sum%10);
    if (sum % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }

    // check length and starting digits
    int starting_digits = check_digit(number, count);
    if (count == 15 && (starting_digits == 34 || starting_digits == 37))
    {

        printf("AMEX\n");
    }
    else if (count == 16 && (starting_digits > 50 && starting_digits <= 55))
    {
        printf("MASTERCARD\n");
    }
    else if ((count == 13 || count == 16) && starting_digits == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

long power(int n, int m)
{
    long result = 1;
    for (int i = 0; i < m; i++)
    {
        result *= n;
    }
    return result;
}

int check_digit(long number, int count)
{
    int start = number / power(10, count - 1);
    if (start == 4)
    {
        return start;
    }
    else
    {
        start = number / power(10, count - 2);
    }
    return start;
}