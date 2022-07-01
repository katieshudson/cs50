#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //variable for name
    string name = get_string("Hey there! What is your name? ");

    // printing a Hello message with a format code of a string
    printf("Hello, %s! It's so nice to meet you.\n", name);
}