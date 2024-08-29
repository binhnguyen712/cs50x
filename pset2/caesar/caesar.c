#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

bool only_digits(string s);
char rotate(char c, int k);

int main(int argc, string argv[])
{
    // Make sure program was run with just one command-line argument
    if (argc != 2){
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // Make sure every character in argv[1] is a digit
    if (only_digits(argv[1]) == false){
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Convert argv[1] from a `string` to an `int`
    int k;
    k = atoi(argv[1]);
    // Prompt user for plaintext
    string plaintext = get_string("plain text:  ");
    // For each character in the plaintext:
    printf("ciphertext: ");
    for (int i = 0; i < strlen(plaintext); i++){
        // Rotate the character if it's a letter
        if (isalpha(plaintext[i])){
            printf("%c", rotate(plaintext[i], k));
        }else{
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
    return 0;
}

bool only_digits(string s){
    bool isdigit = true;
    for (int i = 0; i < strlen(s); i++){
        if(s[i] < 48 || s[i] > 57){
            isdigit = false;
        }
    }
    return isdigit;
}

char rotate(char p, int k){
    char c;
    if (isupper(p)){
        c = (p - 65 + k) % 26;
        return c + 65;
    }else{
        c = (p - 97 + k) % 26;
        return c+ 97;
    }


}
