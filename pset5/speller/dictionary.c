// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26*26 +1;
unsigned int total_words = 0;
// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    unsigned int hash_value = hash(word);
    if(table[hash_value] != NULL ){
        node *temp = table[hash_value];
        while(temp != NULL){
            if (strcasecmp(word, temp->word) == 0){
                return true;
            }
            temp = temp->next;

        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash
    int hash_value = 0;
    int length = strlen(word);
    for(int i = 0; i<length; i++){
        int index = (int)tolower(word[i]) - 'a';
        hash_value += index * i ;
    }

    return hash_value % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *source = fopen(dictionary, "r");
    if(source == NULL){
        printf("Could not open dictionary");
        return 2;
    }
    char word[LENGTH+1];
    while(fscanf(source, "%s", word) != EOF){
        total_words++;
        node *n = malloc(sizeof(node));
        if(n == NULL){
            return false;
        }
        strcpy(n->word, word);
        unsigned int hash_value = hash(n->word);
        if(table[hash_value] == NULL){
            table[hash_value] = n;
            n->next = NULL;
        }else{
            n->next = table[hash_value];
            table[hash_value] = n;
        }
    }

    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return total_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for(int i =0; i < N; i++){
        node *cur = table[i];
        node *temp = table[i];
        while(cur != NULL){
            temp = cur;
            cur = cur->next;
            free(temp);
        }
    }
    return true;
}
