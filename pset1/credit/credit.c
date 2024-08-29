#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>

void check_card(long number);

int main(void)
{
    long number = get_long("Number: ");
    check_card(number);
}

void check_card(long number)
{
    int sum = 0;
    int count = 0;
    long temp_number = number;
    for(int i = 0; number != 0; number /= 10, i++ )
    {
        if (i % 2 == 0)
        {
            sum += number % 10;
        }
        else
        {
            if ((number % 10) * 2 > 9)
            {
                sum += (number % 10 * 2) % 10 + ((number % 10) * 2 / 10);
            }
            else
            {
                sum += (number % 10) * 2;
            }
        }
        count++;
    }
 //   printf("Sum: %i", sum);
   // printf("Count: %i", count);
    if (sum % 10 == 0)
    {
        if (count == 15)
        {
            int amex_start = temp_number / pow(10, 13);
            if(amex_start == 34 || amex_start == 37)
            {
                printf("AMEX");
                printf("\n");
            }
            else
            {
                printf("INVALID");
                printf("\n");
            }
        }
        else if (count == 16)
        {
            int mastercard_start = temp_number / pow(10, 14);
            int visa_start = temp_number / pow(10, 15);
            if (mastercard_start >= 51 && mastercard_start <= 55)
            {
                printf("MASTERCARD");
                printf("\n");

            }
            else if (visa_start == 4)
            {
                printf("VISA");
                printf("\n");
            }
            else
            {
                printf("INVALID");
                printf("\n");
            }
        }
        else if (count == 13)
        {
            int visa_start = temp_number / pow(10, 12);
            if (visa_start == 4)
            {
                printf("VISA");
                printf("\n");
            }
            else
            {
                printf("INVALID");
                printf("\n");
            }
        }
        else
        {
            printf("INVALID");
            printf("\n");
        }
    }
    else
    {
        printf("INVALID");
        printf("\n");
    }
}