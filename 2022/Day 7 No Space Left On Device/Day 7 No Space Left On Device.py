import collections

def filesystem(terminal_output):
    arr = []
    directory_sizes = collections.defaultdict(int)
    for i in terminal_output:
        if i.split()[0].isdigit():
            for j in range(len(arr)):
                directory_sizes["/".join(arr[:1 + j])] += int(i.split()[0])
        if i.split()[1] == "cd":
            directory = i.split()[2]
            if directory != "..":
                arr.append(directory)
            else:
                arr.pop()
    return directory_sizes

def part_one(sorted_sizes):
    return sum(i if i < 1e5 else 0 for i in sorted_sizes)

def part_two(sorted_sizes):
    for i in sorted_sizes:
        if i > 3e7 + directory_sizes["/"] - 7e7:
            return i

terminal_output = open("input.txt").read().splitlines()
directory_sizes = filesystem(terminal_output)
sorted_sizes = sorted(directory_sizes.values())

print("Part One: %d" % part_one(sorted_sizes))
print("Part Two: %d" % part_two(sorted_sizes))