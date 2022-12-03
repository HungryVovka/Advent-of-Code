import pathlib

numbers_of_letters = {
    "a" : 1, "b" : 2, "c" : 3, "d" : 4, "e" : 5, "f" : 6, "g" : 7,
    "A" : 27, "B" : 28, "C" : 29, "D" : 30, "E" : 31, "F" : 32, "G" : 33,
    "h" : 8, "i" : 9, "j" : 10, "k" : 11, "l" : 12, "m" : 13, "n" : 14,
    "H" : 34, "I" : 35, "J" : 36, "K" : 37, "L" : 38, "M" : 39, "N" : 40,
    "o" : 15, "p" : 16, "q" : 17, "r" : 18, "s" : 19, "t" : 20, "u" : 21,
    "O" : 41, "P" : 42, "Q" : 43, "R" : 44, "S" : 45, "T" : 46, "U" : 47,
    "v" : 22, "w" : 23, "x" : 24, "y" : 25, "z" : 26,
    "V" : 48, "W" : 49, "X" : 50, "Y" : 51, "Z" : 52
}


rucksacks = [i.strip() for i in open(pathlib.Path("input.txt"), "r").read().splitlines()]

def rucksack_check(r_1, r_2, r_3 = []):
    if r_3 == []:
        r_3 = r_2
    answer = 0
    arr = []
    for i in r_1:
        if i in arr:
            continue
        if i in r_2 and i in r_3:
            arr.append(i)
            answer += numbers_of_letters[i]
    return answer

rucksack_reorg_1 = 0
for rucksack in rucksacks:
    index = round(len(rucksack) / 2)
    rucksack_reorg_1 += rucksack_check(rucksack[:index], rucksack[index:])

rucksack_reorg_2 = 0
three_elves, all_elves = [], []
for i in rucksacks:
    three_elves.append(i)
    if len(three_elves) == 3:
        all_elves.append(three_elves)
        three_elves = []
for rucksack in all_elves:
    rucksack_reorg_2 += rucksack_check(rucksack[0], rucksack[1], rucksack[2])

print("Part One: %d" % rucksack_reorg_1)
print("Part Two: %d" % rucksack_reorg_2)