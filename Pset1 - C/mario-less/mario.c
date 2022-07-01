#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //variable for height integer in a do while loop
    int n;
    do
    {
        n = get_int("How tall do you want your pyramid to be? (It can be 1 to 8 bricks high) ");
    }
    while (n < 1 || n > 8);  // height can be greater than 0 and less than 9 (1 - 8)


    // nested loops for printing "bricks" --> #
    for (int i = 0; i < n; i++)  // rows
    {
        for (int k = 0; k < (n - (i + 1)); k++) // additional for loop to account for spaces and the right aligned pyramid format
        {
            printf(" ");

        }
        for (int j = 0; j < (i + 1); j++)  // columns
        {

            printf("#");

        }

        // move to next line
        printf("\n");

    }

}
