import collections

def filesystem(terminal_output):
    arr = []
    directory_sizes = collections.defaultdict(int)
    for i in terminal_output:
        j = i.split()
        if j[0].isdigit():
            for k in range(len(arr)):
                directory_sizes["/".join(arr[:1 + k])] += int(j[0])
        if j[1] == "cd":
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

directory_sizes = filesystem(open("input.txt").read().splitlines())
sorted_sizes = sorted(directory_sizes.values())

print("Part One: %d" % part_one(sorted_sizes))
print("Part Two: %d" % part_two(sorted_sizes))