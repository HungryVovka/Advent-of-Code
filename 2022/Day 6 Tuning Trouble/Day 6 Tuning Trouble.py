import collections

def tuning_trouble(part = 1):
    if part == 1:
        marker = 4
    if part == 2:
        marker = 14
    marker_length = marker
    buffer = collections.deque(signal[c] for c in range(marker_length))
    for i in signal[marker_length:]:
        if all(buffer.count(buffer[c]) == 1 for c in range(marker_length)):
            return marker
        else:
            marker += 1
            buffer.popleft()
            buffer.append(i)

signal = open("input.txt").readline().strip()

print("Part One: %s" % tuning_trouble(1))
print("Part Two: %s" % tuning_trouble(2))

# or

def tuning_trouble(part = 1):
    if part == 1:
        marker = 4
    if part == 2:
        marker = 14
    return [a + marker for a, b in enumerate(\
        zip(\
        *list(open("input.txt").read()[i:]\
            for i in range(marker)))) if len(set(b)) == marker][0]

print("Part One: %s" % tuning_trouble(1))
print("Part Two: %s" % tuning_trouble(2))