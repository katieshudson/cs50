// The problem to be solved: Decide which coins and how many of each to hand to the customer.

#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();  // remaining cents

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - (quarters * 25);

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - (dimes * 10);

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - (nickels * 5);

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - (pennies * 1);

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("You will be given %i coins\n", coins);
    // printf("%i\n", coins);
    printf("%i quarters\n", quarters);
    printf("%i dimes\n", dimes);
    printf("%i nickels\n", nickels);
    printf("%i pennies\n", pennies);
}

int get_cents(void) // Ask how many cents the customer is owed
{
    // TODO

    int get_cents_question;
    do
    {
        get_cents_question = get_int("How many cents are you owed? ");
    }
    while (get_cents_question < 0);  // cents owed cannot be negative, thus anything < 0 will prompt a question


    return get_cents_question;
}

int calculate_quarters(int cents)
{
    // TODO

    int num_quarters = cents / 25; // this is integer division

    return num_quarters; // the num of quarters that fit into the cents
}

int calculate_dimes(int cents)
{
    // TODO

    int num_dimes = cents / 10;

    return num_dimes;
}

int calculate_nickels(int cents)
{
    // TODO

    int num_nickels = cents / 5;

    return num_nickels;
}

int calculate_pennies(int cents)
{
    // TODO

    int num_pennies = cents / 1;

    return num_pennies;
}
