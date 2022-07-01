#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))  //! doesnt prevent the function from being called. so vote() is being called here regardless
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)  // return true and increment the vote for candidate
{

    // function looks for a candidate called 'name'
    for (int i = 0; i < candidate_count; i++) // loop through every possible candidate
    {

        if (strcmp(candidates[i].name, name) == 0) // did the candidate name match to what you voted for at [i]
        {
            candidates[i].votes += 1; // increase vote for candidate
            return true; // return true because it's a boolean function. So this means we found a valid vote and we stop looking
        }

    }

    return false; // if you get here, it means you didn't vote for someone valid

}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // variable to keep track of winning votes
    int winning_num_of_votes = 0;

    // figuring out the num of winning votes
    for (int i = 0; i < candidate_count; i++)
    {
        // look at each candidates # of votes, compare to winning votes variable @ 0 to start
        if (candidates[i].votes > winning_num_of_votes)
        {
            winning_num_of_votes = candidates[i].votes; // winning votes variable increases which matches to the winning candidate
        }
    }

    // who is the candidate(s) with the highest # of votes
    for (int i = 0; i < candidate_count; i++) // iterate through each candidate
    {
        if (candidates[i].votes == winning_num_of_votes) // matches candidate votes to winning vote number
        {
            printf("%s\n", candidates[i].name); // prints name that is associated to the candidate with the highest number of votes
        }

    }

    return;
}