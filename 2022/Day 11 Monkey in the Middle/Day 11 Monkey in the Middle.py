import math

def monkey_dict(arr, items, monkey):
    arr.append({
        "items" : items, 
        "operation" : monkey_operation(monkey), 
        "test" : monkey_test(monkey), 
        "rounds" : 0,
        })

def monkey_items(m):
    return [int(i) for i in m[0].strip().split(":")\
                             [1].strip().split(",")]

def monkey_operation(monkey):
    return lambda m: eval(monkey[1]
        .split("=")[1]
        .strip()
        .replace("old", str(m)))

def monkey_test(monkey):
    return lambda m: m_split(monkey, 3, "monkey")\
        if m % m_split(monkey, 2, "by") == 0 else m_split(monkey, 4, "monkey")

def monkeys_rounds(part, arr, m_range, modulo = 0):
    for i in range(m_range):
        for j in arr:
            for k in range(len(j["items"])):
                item = j["items"].pop(0)
                if part == 1:
                    index = math.floor(j["operation"](item) / 3)
                if part == 2:
                    index = j["operation"](item) % modulo
                arr[j["test"](index)]["items"].append(index)
                j["rounds"] += 1
    return arr

def m_split(monkey, index, string):
    return int(monkey[index].split(string)[-1])

def chase_preparation():
    arr = []
    modulo = 1
    for i in monkeys:
        i = i.splitlines()[1:]
        items = monkey_items(i)
        monkey_dict(arr, items, i)
        modulo *= m_split(i, 2, "by")
    return (arr, modulo)

def answer(arr):
    return math.prod(sorted([i["rounds"] for i in arr])[::-1][:2])

def monkey_in_the_middle(part = 1):
    arr = chase_preparation()[0]
    modulo = chase_preparation()[1]
    if part == 1:
        return answer(monkeys_rounds(part, arr, 20))
    if part == 2:
        return answer(monkeys_rounds(part, arr, 10000, modulo))

monkeys = open("input.txt").read().split("\n\n")

print("Part One: %d" % monkey_in_the_middle(1))
print("Part Two: %s" % monkey_in_the_middle(2))