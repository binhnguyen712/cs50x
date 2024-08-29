#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int check_length(long number);
bool check_valid(long number);
void check_amex(long number);
void check_mastercard(long number);
void check_visa(long number, int length);


int main(void)
{
    //declares variables
    long number = get_long("Number: ");
    //check if card valids
    bool valid = check_valid(number);
    //get card length
    int length = check_length(number);

    //If card is valid
    if (valid == true)
    {
        if (length == 15)
        {
            //check amex card
            check_amex(number);
        }
        else if (length == 16)
        {
            //check mastercard and visa
            check_mastercard(number);
        }
        else if (length == 13)
        {
            //check visa
            check_visa(number, length);
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

int check_length(long number)
{
    int count = 0;
    while (number != 0)
    {
        number = number / 10;
        count++;
    }
    return count;
}

bool check_valid(long number)
{
    int sum = 0;
    long new_number = number / 10;
    while (new_number != 0)
    {
        if ((new_number % 10) * 2 > 9)
        {
            sum += (new_number % 10 * 2) %10 + (new_number % 10 * 2) / 10;
        }
        else
        {
             sum += (new_number % 10) * 2;
        }
        new_number = new_number / 100;
    }
    while (number != 0)
    {
        sum += number % 10;
        number = number / 100;
    }
    if (sum % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }

}

void check_amex(long number)
{
    long amex_start = number / pow(10, 13);
    if (amex_start == 34 || amex_start == 37)
    {
         printf("AMEX");
         printf("\n");
    }
    else
    {
        printf("INVALID");
        printf("\n");
    }
    return;
}

void check_mastercard(long number)
{
    long mastercard_start = number / pow(10,14);
    long visa_start = number / pow(10,15);
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
    return;

}

void check_visa(long number, int length)
{
    long visa_start = number /pow(10, 12);
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
    return;
}
