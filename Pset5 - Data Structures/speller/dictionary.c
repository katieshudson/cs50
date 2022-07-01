// Implements a dictionary's functionality

#include <ctype.h> // toupper(), tolower(),
#include <stdbool.h>
#include <stdio.h> // in order to use fopen(), and fscanf()
#include <stdlib.h> // for malloc()
#include <string.h> // strcpy(), strlen()
#include <cs50.h> // strcasecmp()
#include <strings.h> // strcasecmp()
#include <stdint.h>




#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];  // + 1 to include the /0 at the end of every string
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

unsigned int word_count = 0; // keep track of # of words

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO

    /* Pseudocode */
    // get index value of the word -> use hash function
    // enter the linked list, and perform linear search to compare word to each word in linked list
    // if word is found, return true (meaning word is a) spelled correctly and thus b) in dictionary)
    // if word is not found (ie. you get to NULL), word is misspelled or not in dictionary

    // get index value of the word -> use hash function
    unsigned int hash_value = hash(word);

    // variable to keep track of where you are in the linked list and what you are pointing to at given hash table location (index N)
    node *cursor = table[hash_value];  // cursor points to first node of linked list

    while (cursor != NULL) // while the next value in the node != NULL, do this
    {
        // use cursor->word to compare what's inside the cursor node to the word that's in the regular node
        if (strcasecmp(word, cursor->word) == 0) // if 2 strings == 0, word is in dictionary
        {
            return true;
        }

        cursor = cursor->next;  // if cursor doesn't match the word, then move to next node in linked list and repeat loop

    }

    return false; // cursor reached NULL and thus word is not in the dictionary
}

// Hashes word to a number
unsigned int hash(const char *word)
{

    // TODO: Improve this hash function

    /* Pseudocode */
    // Calculate a "Score" aka a number value for the first letter of the word
    // Make hash function case insensitive - convert string to all lower (ie. how to deal with APple)
    // convert char* (string) into a ASCII value... decide how many characters to use? start with 1?
    // take converted number and hash it to get key: (ASCII value % table size)

    // Hashing method inspired from: https://www.educba.com/hashing-function-in-c/

    /* DETERMINE LETTER SCORE */
    int letter_score = 0;

    letter_score = tolower(word[0]); // force first letter to be lower case, and use ASCII value as letter score


    /* HASH LETTER VALUE TO GET KEY */
    unsigned int key = (letter_score % N); // N = number of buckets in table

    return key;


}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // do we need a buffer array to read words into?
    int buffer_length = LENGTH + 1;  // adding 1 for the NULL character
    char buffer[buffer_length];

    // TODO

    // Open up the dictionary file. (char *dictionary represents the dictionary file)
    FILE *file = fopen(dictionary, "r");
    if (file == NULL) // if file cannot be opened, inform the user
    {
        printf("Error: file cannot be opened. Please try again.\n");
        return false;
    }

    // Read strings from the file one at a time (one word in the dictionary at a time)
    while (fscanf(file, "%s", buffer) != EOF)
    {
        node *new_node = malloc(sizeof(node)); // allocating memory for new node pointer

        if (new_node == NULL) // if malloc returns NULL then you're out of memory
        {
            return false;
        }

        // For each word, create a new node for each word (a node will have a value and a next pointer)
        strcpy(new_node->word, buffer); // destination = new_node, source = buffer,
        new_node->next = NULL; // when you dont know what's next, set it to NULL

        // Hash word using hash function to obtain a hash value - returns index into your hash table to determine which of those linked lists you should use when you’re inserting a node into a linked list
        int hash_value = hash(buffer); // returns index for hash table
        // int hash_value = 1; // returns index for hash table  ***FOR TESTING PURPOSES***

        // Take each word, and insert node into hash table at that location
        new_node->next = table[hash_value]; // make new node point to start of correct linked list based on hash value.

        // value stored at table[n] is a pointer**
        table[hash_value] = new_node; // reassigning the head of the list to the newly inserted node

        word_count++; // increase word counter (update size of dictionary)
    }

    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{

    return word_count;

}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO

    // iterate over hash table, and go through each linked list and call free() on all of the nodes
    for (int i = 0; i < N; i++) // for loop first, to go over each of the N places in the table, which is a set number.
    {
        node *head = table[i]; // set head to first node in linked list at hash table[i] location

        while (head != NULL) // keep iterating through linked list bc cursor does not equal NULL
        {
            node *tmp = head; // secondary tmp variable sets to same position as head

            head = head->next; // move head forward in linked list
            free(tmp); // free previous node that cursor WAS pointing to
            tmp = head;
        }

        // exits while statement when cursor == NULL, meaning it reached the end of linked list
        // can now move on to next i index position

        if (head == NULL && i == N - 1)
        {

            return true;

        }

    }

    return false;

}
