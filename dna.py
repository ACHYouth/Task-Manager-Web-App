from sys import exit, argv
import csv


def main():
    if len(argv) != 3:
        print("Command-line argument: python dna.py file.csv file.txt")
        exit(1)

    database = []
    with open(argv[1], "r") as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            for key in row.keys():
                if key == "name":
                    continue
                row[key] = int(row[key])

            database.append(row)
        sequences = (reader.fieldnames)
        del(sequences[0])

    with open(argv[2], "r") as txtfile:
        person_dna = txtfile.readline()

    person_match = {}
    for nucleotides in sequences:
        person_match.update({nucleotides: max_match(person_dna, nucleotides)})

    print(check(database, sequences, person_match))

def max_match(dna, nucleotides):
    match = 0
    for i in range(dna.find(nucleotides), len(dna)):
        # Checks the number of consecutive matches and stores the maximum value
        # i:i+len(nucleotides) returns the nucleotide substring
        if dna[i:i+len(nucleotides)] == nucleotides:
            i, tmp = number_match(i, dna, nucleotides)
            if tmp > match:
                match = tmp
    return match

def number_match(cursor, dna, nucleotides):
    number = 0
    while(dna[cursor:cursor+len(nucleotides)] == nucleotides):
        number += 1
        cursor += len(nucleotides)

    return cursor, number

def check(database, sequences, person_match):
    cont = 0
    for dic in database:
        for key in sequences:
            if dic[key] == person_match[key]:
                cont += 1
        if cont == len(sequences):
            return dic["name"]
        cont = 0
    return "No match"


if __name__ == "__main__":
    main()