all_calories = [i.strip() for i in open("input.txt")]
food = [[]]
for i in all_calories:
    if i == "":
        food.append([])
    else:
        food[-1].append(int(i))
sum_calories = sorted(sum(i) for i in food)[::-1]

print("Part One: %d" % sum_calories[0])
print("Part Two: %d" % sum(sum_calories[:3]))