#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <math.h>
#include <ctype.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    //declare variables
    string text = get_string("Text: ");
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);
    //calculate grade
    printf("%i",letters);
    printf("%i",words);
    printf("%i",sentences);
    float index = 0.0588 * (((double)letters / words) * 100) - 0.296 * (((double)sentences / words) * 100) - 15.8;
    //print grade
    if(index < 1)
    {
        printf("Before Grade 1");
        printf("\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+");
        printf("\n");
    }
    else
    {
        printf("Grade %i", (int) round(index));
        printf("\n");
    }

}

int count_letters(string text)
{
    int count = 0;
        //iterate through text to find # of letters
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        //check if the letter is alphabetical
        if (isalpha(text[i]))
        {
            count++;
        }
    }
    return count;
}

int count_words(string text)
{
    int count = 1;
        //iterate through text to find # of words
    for(int i = 0, n = strlen(text); i < n; i++)
    {
        // check for every space
        if(isspace(text[i]))
        {
            count++;
        }
    }
    return count;
}

int count_sentences(string text)
{
    int count = 0;
    //iterate through text to find # of sentences
    for(int i = 0, n = strlen(text); i < n; i++)
    {
        //check for ! ? .
        if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            count++;
        }
    }
    return count;
}
