/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#include "dictionary.h"

#define HASHSIZE 1000

// initialize node struct
typedef struct node
{
    char word[LENGTH + 1];
    struct node* next;
} node;

//Initialize hashtable and dictionary counter
node* hashtable[HASHSIZE];
int wordcount = 0;

// create hash function
int hash (const char* word)
{
    // initialize hash
    int hash = 0;

    for (int i = 0 ; word[i] != '\0' ; i++)
    {
        hash = hash + word[i];
    }
    return hash % HASHSIZE;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // initialize word
    char word[LENGTH+1];

    // open dictionary
    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }
    
    // check dictionary line by line
    while (!feof (fp))
    {        
        // read from file and input a word in new node
        fscanf(fp, "%s\n", word);
        
        // initialize new word
        node* newword = malloc(sizeof(node));
        
        // copy word in the new node
        strcpy(newword->word, word);
        
        // create index to keep track of hash buckets
        int index = hash(word);
        
        // insert if bucket is empty at index
        if (hashtable[index] == NULL)
        {
            hashtable[index] = newword;
            newword->next = NULL;
        }

        // insert if bucket is not empty at index
        else
        {
            newword->next = hashtable[index];
            hashtable[index] = newword;
        } 

        // increment dictionary
        wordcount++;
    }

    // close dictionary
    fclose(fp);
    
    // end of loading
    return true;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // create variables to check the word
    char checkword[LENGTH+1];

    // convert word to lowercase checkword 
    for(int i = 0, length = strlen(word); i < length; i++)
        checkword[i] = tolower(word[i]); 
    checkword[length] = '\0';

    // find what index of the array the checkword should go in
    int index = hash(checkword);

    // check if the table is empty at this bucket (easy one)
    if (hashtable[index] == NULL)
        return false;

    // create pointer to compare checkword to word
    node* ptr = hashtable[index];
    
    // iterate through bucket and compare checkword to word in there
    while (ptr != NULL)
    {
        if (strcmp(checkword, ptr->word) == 0)
        {
            return true;
        }
        ptr = ptr->next;
    }

    // didn't find the word
    return false;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return wordcount;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // iterate over each hash bucket
    for(int i = 0; i < HASHSIZE; i++)
    {
        // create node to track unloading process
        node *eraser = hashtable[i];

        // iterate over each word in bucket
        while (eraser != NULL)
            {
                node *n = eraser;
                eraser = eraser->next;
                free(n);
            }
    }
    return true;
}
