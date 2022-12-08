def treeetop(part = 1):
    answer = 0
    for i in range(1, len(trees) - 1):
        for j in range(1, len(trees[i]) - 1):
            if part == 1:
                answer += part_one(i, j)
            if part == 2:
                answer = part_two(i, j, answer)
    if part == 1:
        answer += 2 * (len(trees) + len(trees[0])) - 4
    return answer

def array(i, j):
    return [[trees[k][j] for k in range(1 + i, len(trees))],
            [trees[k][j] for k in range(i)],
            trees[i][j + 1:],
            trees[i][:j]]

def part_one(i, j):
    return any(all(x < trees[i][j] for x in y) for y in array(i, j))

def part_two(i, j, answer):
    arr = array(i, j)
    arr[1], arr[3] = arr[1][::-1], arr[3][::-1]
    points_of_view = 1
    for k in arr:
        scorer = 0
        for l in k:
            scorer += 1
            if l >= trees[i][j]:
                break
        points_of_view *= scorer
    return max(answer, points_of_view)

trees = [[int(x) for x in y] for y in open("input.txt").read().splitlines()]

print("Part One: %d" % treeetop(1))
print("Part Two: %d" % treeetop(2))