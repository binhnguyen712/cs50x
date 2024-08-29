import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("invalid command line argument")
        sys.exit(1)
    # TODO: Read database file into a variable
    database = []
    with open(sys.argv[1], 'r') as file:
        reader = csv.reader(file)
        for row in reader:
            database.append(row)
    subsequences = database[0][1:]
    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], 'r') as file:
        sequence = file.readline()

    # TODO: Find longest match of each STR in DNA sequence
    length =[]
    for subsequence in subsequences:
        length.append(longest_match(sequence, subsequence))
    result = [str(i) for i in length]
    # TODO: Check database for matching profiles
    match = False
    for item in database:
        if item[1:] == result:
            print(item[0])
            match = True
            break
    if match == False:
        print("No match")
    return


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


main()
