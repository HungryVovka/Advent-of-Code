def rope_bridge(part = 1):
    if part == 1:
        tail = (0, 0)
        stepped = {tail}
    if part == 2:
        tail = [(0, 0) for x in range(10)]
        stepped = {tail[-1]}
    return visited_maker(part, stepped, tail)

def visited_maker(part, stepped, tail, head = (0, 0)):
    steps = ((y, int(x)) for y, x in (s.split() for s in rope_bridge_steps))
    for i in steps:
        for j in range(i[1]):
            if part == 1:
                head = make_var_a(head, directions[i[0]])
                tail = abs_compare(head, tail)
                stepped.add(tail)
            if part == 2:
                tail[0] = make_var_a(tail[0], directions[i[0]])
                for k in range(len(tail) - 1):
                    tail[k + 1] = abs_compare(tail[k], tail[k + 1])
                stepped.add(tail[-1])
    return len(stepped)

def make_var_a(a, key):
    return (a[0] + key[0], a[1] + key[1])

def compare(a, b):
    return 1 if a > b else - 1

def abs_compare(a, b):
    if abs(a[0] - b[0]) > 1:
        b = (b[0] + compare(a[0], b[0]), b[1])
        if abs(a[1] - b[1]) > 0:
            b = (b[0], b[1] + compare(a[1], b[1]))
    if abs(a[1] - b[1]) > 1:
        b = (b[0], b[1] + compare(a[1], b[1]))
        if abs(a[0] - b[0]) > 0:
            b = (b[0] + compare(a[0], b[0]), b[1])
    return b

directions = {"U" : [0, 1], "R" : [1, 0], "D" : [0, -1], "L" : [-1, 0]}

rope_bridge_steps = open("input.txt").read().splitlines()

print("Part One: %d" % rope_bridge(1))
print("Part Two: %d" % rope_bridge(2))