#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/*  TO DO: implement a program that calculates the approximate grade level needed to comprehend some text */

int calculate_index(int char_count, int word_count, int sentence_count);
int calculate_letters(string s);
int calculate_words(string s);
int calculate_sentences(string s);

int main(void)
{
    // TO DO
    // 1) input text from user (get_string -- "Text:  ")

    // 2) analyze text with formula to determine grade level
    // - count number of total letters total
    // - count number of sentences
    // - count number of words
    // - Calculate "L" = number of letters per 100 words (letters / words * 100 = L)
    // - Calculate "S" = number of sentences per 100 words (sentences / 14 words * 100 = S)

    // 3) output grade level of text (ie. Grade 3) (printf "Grade %i <--- int from calculation)


    /* ACCEPT USER TEXT INTPUT */
    string text = get_string("Text: ");

    /* ANALYZE TEXT WITH FORMULA TO DETERMINE GRADE LEVEL */
    int char_count = calculate_letters(text);
    int word_count = calculate_words(text);
    int sentence_count = calculate_sentences(text);
    int grade_level_index = calculate_index(char_count, word_count, sentence_count);

    // printf("%i Letters\n", char_count);
    // printf("%i Words\n", word_count);
    // printf("%i Sentences\n", sentence_count);

    // /* OUTPUT - GRADE LEVEL */
    if (grade_level_index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade_level_index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade_level_index); // print grade_level from function using %i
    }
}


int calculate_index(int char_count, int word_count, int sentence_count)
{
    int grade_level = 0;
    float l_per_hundred = 0; // "L" - letters per 100 words
    float s_per_hundred = 0; // "S" - sentences per 100 words

    // Calculate L - (letters / words * 100 = L)
    l_per_hundred = (float)(char_count) / (float)(word_count) * 100;

    // Calculate S - (sentences / words * 100 = S)
    s_per_hundred = ((float)(sentence_count) / word_count) * 100;

    // Calculate index grade_level with Coleman-Liau index formula = (0.0588 * L) - (0.296 * S) - 15.8
    grade_level = round(0.0588 * l_per_hundred - 0.296 * s_per_hundred - 15.8); //

    return grade_level;

}


int calculate_letters(string s)
{
    int char_count = 0; // count characters from string s input

    // Count Letters (Characters)
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (isupper(s[i]) || islower(s[i]))
        {
            char_count += 1;
        }
    }

    return char_count;
}

int calculate_words(string s)
{
    int word_count = 0; // count words from string s input.
    int string_length = strlen(s);

    for (int i = 0, n = string_length + 1; i < n; i++) // need to string_length + 1 because it exits before it counts the NULL
    {
        if (s[i] == 32 || s[i] == 0)
        {
            word_count += 1;
        }
    }

    return word_count;
}

int calculate_sentences(string s)
{
    int sentence_count = 0; // count sentences from string s input

    // Count Sentences - any occurrence of a period (.), exclamation point (!), or question mark (?) indicates the end of a sentence.
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (s[i] == 46 || s[i] == 33 || s[i] == 63) // ASCII codes --> 46 = . | 33 = ! | 63 = ?
        {
            sentence_count += 1;
        }
    }

    return sentence_count;

}