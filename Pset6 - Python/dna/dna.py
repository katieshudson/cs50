import csv
import sys


def main():

    # first filename variable (.csv file)
    csv_file = sys.argv[1]

    # second filename variable (.txt file)
    txt_file = sys.argv[2]

    # TODO: Check for command-line usage
    # Ensure correct usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    # TODO: Read database csv file into a variable - should be a dictionary

    # database variable (will house dictionaries)
    dna_database = {}

    # create list to store fieldnames
    search_sequences = []

    with open(csv_file) as file:  # using with open means you don't need "r" and dont need to remember to close it
        reader = csv.DictReader(file)  # reads one line of file and gives dictionary back
        search_sequences = reader.fieldnames[1:]  # contains all STR fieldnames, splicing from name onwards
        for user_data in reader:
            for field in search_sequences:
                user_data[field] = int(user_data[field])  # converting each STR string count to an int
            user_name = user_data.pop('name')  # remove name field and return its value to user_name variable
            dna_database[user_name] = user_data  # adding a new key to the dictionary. Adding name as key to STR values

    # TODO: Read DNA sequence file into a variable

    # dna sequence variable
    dna_sequence = ''  # empty string

    with open(txt_file, 'r') as txt:
        dna_sequence = txt.read()

    # TODO: Find longest match of each STR in DNA sequence - leverage helper function

    max_str_count = {}  # will store the counts of each STR pattern in a dictionary {STR, count}

    for subsequence in search_sequences:
        # add new key-value pair to dictionary to track subsequence (STR) to its count
        max_str_count[subsequence] = longest_match(dna_sequence, subsequence)

    # # TODO: Check database for matching profiles

    match_found = False
    for user_name, user_data in dna_database.items():  # iterating through the dictionary to compare user_data with the max_str_count
        if max_str_count == user_data:  # compare user_data with the max_str_count
            match_found = True
            print(user_name)

    if not match_found:
        print("No match")

    return
#    my_db = [{'name': 'Alice', 'AGATC': 2, 'AATG': 8, 'TATC': 3}, {'name': 'Bob', 'AGATC': 4, 'AATG': 1, 'TATC': 5}, {'name': 'Charlie', 'AGATC': 3, 'AATG': 2, 'TATC': 5}]
#    my_db = {'Alice': {'AGATC': 2, 'AATG': 8, 'TATC': 3}, 'Bob': 'AGATC': 4, 'AATG': 1, 'TATC': 5}}

    # my_db = {username: user_dna_sequences}
    # user_dna_sequences = {subsequence: count, subsequence2: count2 }


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


if __name__ == "__main__":
    main()
