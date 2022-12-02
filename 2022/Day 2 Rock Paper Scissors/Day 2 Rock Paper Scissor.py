import pathlib

part_one = {
    "A X" : 4, "B X" : 1, "C X" : 7, 
    "A Y" : 8, "B Y" : 5, "C Y" : 2,
    "A Z" : 3, "B Z" : 9, "C Z" : 6
}

part_two = {
    "A X" : 3, "B X" : 1, "C X" : 2,
    "A Y" : 4, "B Y" : 5, "C Y" : 6,
    "A Z" : 8, "B Z" : 9, "C Z" : 7
}

def part_one_values(key):
    return part_one[key]

def part_two_values(key):
    return part_two[key]

RPS_input = open(pathlib.Path("input.txt"), "r").read().splitlines()
RPS_answer_1 = sum(part_one_values(i) for i in RPS_input)
RPS_answer_2 = sum(part_two_values(i) for i in RPS_input)
print("Part One: %d" % RPS_answer_1)
print("Part Two: %d" % RPS_answer_2)