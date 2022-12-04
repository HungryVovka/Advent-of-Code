def variety(a, b):
    return set(range(int(a), int(b) + 1))

def camp_cleanup(part = 1):
    answer = 0
    for i in open("input.txt"):
        (pair1, pair2) = i.strip().split(",")
        (pair1_1, pair1_2), (pair2_1, pair2_2) = pair1.split("-"), pair2.split("-")
        variety_1, variety_2 = variety(pair1_1, pair1_2), variety(pair2_1, pair2_2)
        if part == 1:
            if variety_1.issubset(variety_2) or variety_2.issubset(variety_1):
                answer += 1
        if part == 2:
            if not variety_1.isdisjoint(variety_2):
                answer += 1
    return answer

print("Part One: %d" % camp_cleanup(1))
print("Part Two: %d" % camp_cleanup(2))