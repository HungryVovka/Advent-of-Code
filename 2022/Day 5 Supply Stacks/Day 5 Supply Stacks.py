import re

supply_info = open("input.txt").read().split("\n")

def crates_nesting(len_crates):
    return [[] for i in range(len_crates)]

def enumerate_crates(crates):
    for i in all_crates[:-1][::-1]:
        index = 1
        for a, b in enumerate(crates):
            if i[index] != " " and index < len(i):
                b.append(i[index])
            index += 4
    return crates

def part_one(crates, amount, start, finish):
    return [crates[finish].append(crates[start].pop()) for i in range(amount)]

def part_two(crates, amount, start, finish):
    the_crateMover_9001 = crates[start][-amount:]
    crates[start] = crates[start][:-amount]
    crates[finish].extend(the_crateMover_9001)
    return crates

all_move = supply_info[supply_info.index("") + 1:]
all_crates = supply_info[:supply_info.index("")]
len_crates = len(re.sub(" ", "", all_crates[-1]))

def supply_stacks(part = 1):
    crates = crates_nesting(len_crates)
    enumerate_crates(crates)
    for i in all_move:
        if i == "":
            continue
        amount = int(i.split(" ")[1])
        start = int(i.split(" ")[3]) - 1
        finish = int(i.split(" ")[5]) - 1
        if part == 1:
            part_one(crates, amount, start, finish)
        if part == 2:
            part_two(crates, amount, start, finish)
    return "".join(i[-1] for i in crates)

print("Part One: %s" % supply_stacks(1))
print("Part Two: %s" % supply_stacks(2))