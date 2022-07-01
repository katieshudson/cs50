#include <cs50.h>
#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

bool only_digits(string s);
char rotate_char(char c, int key);

int main(int argc, string argv[])
{

    // TO DO
    // 1. get key
    // 2. get plaintext
    // 3. encipher
    // 4. print ciphertext

    int key = 0;

    /* GET THE KEY */
    //user decides on value of key, using an command line argument

    if (argc != 2) // checking the number of arguments in your command line
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    if (only_digits(argv[1]) != true) // if a non digit is provided
    {
        printf("Usage: ./caesar key\n"); // prompt user with error message on how to input what is actually needed
        return 1;
    }

    key = atoi(argv[1]); // converts string to int and gives you the int key

    /* GET PLAINTEXT */
    // use get_string to prompt the user for some plaintext with ("plaintext: ")

    string plaintext = get_string("plaintext:  ");


    /* PRINT CIPHERTEXT */

    printf("ciphertext: ");

    // for every character in plaintext, rotate the character if it's a letter with the key int, if non-letter keep it as is
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        // check for letter vs special character
        if (isalpha(plaintext[i]))
        {
            printf("%c", rotate_char(plaintext[i], key));

        }
        else
        {
            // use the non-letter, special character as is
            printf("%c", plaintext[i]);
        }

    }

    printf("\n");

    return 0;  // program exits by returning 0 from main --> "0" in C means true.
}


bool only_digits(string s) // boolean function that tells you if the commandline argv is a digit from 0 to 9
{

    for (int i = 0, n = strlen(s); i < n; i++)
    {
        // isdigit(char c) checks if char is a digit between 0 to 9
        if (isdigit(s[i]) == 0) // if isdigit(char c) returns a zero, c is a a non-digit
        {
            return false;
        }

    }

    return true;


}

/* ENCIPHER */
char rotate_char(char c, int k) // takes char as input and also an int and rotates that char by the many positions if it's a letter
{

    int conversion_offset = 65; // assume input is uppercase

    // encrypt letter
    if (islower(c)) // check if lowercase
    {
        conversion_offset = 97; // change offset needed for lowercase

    }

    int ascii_value = c - conversion_offset; // convert ASCII to alphabetical index
    int shifted_letter = (ascii_value + k) % 26; // shift alphabetical using formula
    int convert_back = shifted_letter + conversion_offset; // convert back to ASCII

    return convert_back;

}