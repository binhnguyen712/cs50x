#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int h;
    // loops to repeat if user enter wrong input
    do
    {
        //prompt user to get height
        h = get_int("Height: ");
        //condition to inform user to enter correct
        if (h > 8 || h < 1)
        {
            printf("Please enter a height from 1 to 8!");
            printf("\n");
        }

    }
    while (h < 1 || h > 8);

    //loops to print pyramid
    for (int i = 0; i < h; i++)
    {
        for (int j = h - 1; j >= 0; j--)
        {
            if (j > i)
            {
                printf(" ");
            }
            else
            {
                printf("#");

            }
        }
        printf("  ");
        for (int k = 0; k <= i; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}

