#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // prompt user to enter name
    string name = get_string("What's your name ? ");
    //print name
    printf("hello, %s\n", name);
}