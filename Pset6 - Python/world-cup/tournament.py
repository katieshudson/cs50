# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000

def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []

    # filename variable
    filename = sys.argv[1]

    with open(filename) as file:  # using with open means you don't need "r" and dont need to remember to close it
        reader = csv.DictReader(file)  # reads one line of file and gives dictionary back
        for team in reader:  # team is like i in a for loop, it's a variable that's established for the loop
            team["rating"] = int(team["rating"])  # convert rating string into int
            teams.append(team)  # take each dictionary {team, rating} and append it (store it) to list

    counts = {}
    # Simulate N tournaments and keep track of win counts
    # keys are names of teams, values are how many tournaments won for each team

    for i in range(N):
        winning_team = simulate_tournament(teams)  # who won each tournament?

        # check if team is in dictionary
        if winning_team in counts:  # team is in dictionary
            counts[winning_team] += 1  # increase # of tournaments won by 1
        else:  # team is not in dictionary
            counts[winning_team] = 1  # initialize first win for team

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    # Simulate a tournament. Return name of winning team.
    # once you have 1 team then you can return that name, and use it in the counts dictonary

    while len(teams) > 1:  # as long as there is more than 1 team, simulate another round
        teams = simulate_round(teams)  # re-update the list of teams

    return teams[0]["team"]  # you only care about returning name of team


if __name__ == "__main__":
    main()
