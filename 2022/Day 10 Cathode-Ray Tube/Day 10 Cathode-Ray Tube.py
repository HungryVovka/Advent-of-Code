def cathode_ray_tube(part = 1):
    x_register, cycle = 1, 1
    crt = crt_signals(x_register, cycle)
    image = image_draw(crt)
    if part == 1:
        return sum(crt[v] * v for v in [20 + 40 * i for i in range(6)])
    if part == 2:
        return "\n" + "\n".join("".join(pixel) for pixel in image)

def crt_signals(x_register, cycle):
    crt = {}
    for x in instructions:
        crt[cycle] = x_register
        if x != "noop":
            crt[cycle + 1] = x_register
            cycle += 2
            x_register += int(x.split()[1])
        else:
            cycle += 1
    return crt

def image_draw(crt):
    image = [["_"] * 40 for i in range(6)]
    for i in range(240):
        if i % 40 >= crt[i + 1] - 1 and i % 40 <= crt[i + 1] + 1:
            image[i // 40][i % 40] = "$"
    return image

instructions = [i.strip() for i in open("input.txt")]

print("Part One: %d" % cathode_ray_tube(1))
print("Part Two: %s" % cathode_ray_tube(2))