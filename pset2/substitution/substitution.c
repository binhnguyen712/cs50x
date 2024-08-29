#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char swap(char c, string k);
bool validkey(string s);

int main(int argc, string argv[]){
    // make sure only one command line argument
    if (argc != 2){
        printf("Usage: ./substitution key");
        return 1;
    }
    // check if the key is valid
    if(validkey(argv[1]) == false){
        printf("Usage: ./substitution key");
        return 1;
    }
    // input
    string plaintext = get_string("plaintext:  ");
    printf("ciphertext: ");
    for (int i = 0; i < strlen(plaintext); i++){
        if(isalpha(plaintext[i])){
            printf("%c", swap(plaintext[i], argv[1]));
        }else{
            printf("%c", plaintext[i]);
        }

    }
    printf("\n");
    return 0;
}

bool validkey(string s){
    int arr[26] = {0};
    if (strlen(s) != 26){
        return false;
    }else{
        for (int i = 0; i < strlen(s); i++){
            if (!isalpha(s[i]) || arr[s[i] - 97] == 1 ){
                return false;
                break;
            }else{
                arr[s[i] - 97] = 1;
            }
        }
    }
    return true;

}
char swap(char c, string k){
    if(islower(c)){
        c = k[c - 97];
        return tolower(c);
    }else{
        c = k[c - 65];
        return toupper(c);
    }

}
