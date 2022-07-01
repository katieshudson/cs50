#include <cs50.h>
#include <stdio.h>
#include <string.h>


// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] stores the index of candidate for voter[i] at preference[j]
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Number of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++) // initializing the array with starting values
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++) // iterate through number of voters
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated) // if candidate is still in race, eliminated = false
                {
                    printf("%s\n", candidates[i].name); // print candidate(s) name
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)  // keep track of all of voter preferences
{
    // int voter = which number voter is currently voted (i)
    // rank = 0 --> 1st preference (j), 1 --> 2nd preference... etc

    // is there a match for the name of a valid candidate?
    for (int i = 0; i < candidate_count; i++) // iterate through all candidates
    {
        if (strcmp(candidates[i].name, name) == 0) // compare name strings with strcmp()
        {
            // if name is a match, update global preferences array
            // to indicate that the int voter has candidate [i] at int rank
            preferences[voter][rank] = i;  // storing candidate index and their associated voter preference

            // If preference is successfully recorded, the function returns true
            return true;
        }
    }

    // function returns false otherwise (ie. name is not name of one of the candidates)
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // go through each voter, and update vote count for candidates who are still in the race (non-emliminated candidates)
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++) // [j] is the preference, and there are the same number slots of preferences as candidates
        {
            if (candidates[preferences[i][j]].eliminated == false)
            {
                candidates[preferences[i][j]].votes += 1; // increase vote for candidate
                break;
            }
        }
    }

    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{

    for (int i = 0; i < voter_count; i++) // iterate through voters
    {
        int half_vote = voter_count / 2;
        if (candidates[i].votes > half_vote) // calculate candidate votes vs total votes, does candidate have majority?
        {
            printf("print_winner - ENTERS - IF THERES A MAJORITY\n");
            printf("%s\n", candidates[i].name); // if true, then print candidate name
            return true;
        }
    }

    printf("print_winner - ENTERS - NO MAJORITY - returns false\n");
    return false; // if candidate does not have majority (total votes < 50%), return false (ie. no winner)
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min_votes; // variable to house the min number of votes candidate(s) have

    for (int i = 0; i < candidate_count; i++) // iterate through the # of candidates
    {
        if (candidates[i].eliminated == false && candidates[i].votes < min_votes) // check if candidate is still in election
        {
            min_votes = candidates[i].votes; // update min # of votes variable
        }
    }

    return min_votes; // return the min # of votes
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{

    for (int i = 0; i < candidate_count; i++) // itereate through candidates
    {
        // check if candidate is still in election AND if their num of votes == min # of votes
        if (candidates[i].eliminated == false && candidates[i].votes == min)
        {
            printf("is_tie - enters into eliminated = false and votes = min");
            return true; // return true = tie election
        }
    }
    printf("is_tie - enters into return false");
    return false; // no tie between candidates
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{

    for (int i = 0; i < candidate_count; i++) // iterate through # of candidates
    {
        // a) is the candidate still in race? AND b) does candidate's vote count count = min vote count?
        if (candidates[i].eliminated == false && candidates[i].votes == min)
        {
            candidates[i].eliminated = true; // eliminate candidate from election, change status to true
        }
    }

    return;
}