#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    // compare the scores of the words

    if (score1 > score2) // if word1 has a higher score, player 1 wins
    {
        printf("Player 1 Wins!\n");
    }
    else if (score1 < score2) // if word2 has a higher score, player 2 wins
    {
        printf("Player 2 Wins!\n");

    }
    else // if tie word1 == word2, tie game
    {
        printf("Player 1 and Player 2 tie! Try again!\n");
    }

}

int compute_score(string word)
{
    // TODO: Compute and return score for string

    int word_score = 0;

    // need to handle upper and lower case words
    for (int i = 0, n = strlen(word); i < n; i++)  // iterate over array, character by character
    {
        // check if character is upper or lower case
        if (isupper(word[i])) // if character is uppercase (TRUE)
        {
            //subtract 65 from the value of the char to get the POINTS[n] position
            word_score += POINTS[word[i] - 65];
        }
        else if (islower(word[i])) // if lower case (TRUE) then...
        {
            //subtract 97 from the value of char to get POINTS[n] position
            word_score += POINTS[word[i] - 97];
        }
    }


    // return computed score of a word stored in variable word_score
    return word_score;


}
