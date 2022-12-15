from collections import deque
from itertools import count

def directions_arr(hor, vert, cur_pos):
    return [(a, b) for a in range(hor)\
        for b in range(vert) if hill[a][b] in cur_pos]

def marks(char):
    match char:
        case "E":
            return marks("z")
        case "S":
            return marks("a")
        case _:
            return ord(char)

def hill_climbing(part = 1):
    if part == 1:
        cur_pos = "S"
    if part == 2:
        cur_pos = "Sa"
    hor, vert = len(hill), len(hill[0])
    search_place = deque(directions_arr(hor, vert, cur_pos))
    stepped = set(search_place)
    for i in count(1):
        for j in range(len(search_place)):
            a, b = search_place.popleft()
            directions = [[a, b + 1], [a + 1, b], [a, b - 1], [a - 1, b]]
            for ax, bx in directions:
                if (ax, bx) not in stepped\
                    and ax in range(hor)\
                    and bx in range(vert)\
                    and marks(hill[a][b]) + 1 >= marks(hill[ax][bx]):
                    if hill[ax][bx] == "E":
                        return i
                    stepped.add((ax, bx))
                    search_place.append((ax, bx))

hill = [list(i.strip()) for i in open("input.txt")]

print("Part One: %d" % hill_climbing(1))
print("Part Two: %d" % hill_climbing(2))