import csv
import sys


def main():
    if (len(sys.argv) != 3):
        print("Usage:\n    python3 dna.py [database.csv] [sequence.txt]")
        sys.exit(1)

    db_file = open(sys.argv[1])
    db_reader = csv.DictReader(db_file)

    with open(sys.argv[2]) as file:
        sequence = file.read().strip()
    
    match = get_match(db_reader, sequence)
    print(match)

    return


def get_match(db_reader, sequence):
    subsequences = db_reader.fieldnames[1:]
    for person in db_reader:
        if person_matches(sequence, subsequences, person):
            return person['name']
    
    return 'No match'


def person_matches(sequence, subsequences, person):
    for subsequence in subsequences:
        sub_match = longest_match(sequence, subsequence)
        if int(person[subsequence]) != sub_match:
            return False
    
    return True


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
