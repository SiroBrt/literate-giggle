def cycle_lenght(n, dick):
    if n not in dick.keys():
        if n % 2 == 0:
            dick[n] = 1 + cycle_lenght(n // 2, dick)
        else:
            dick[n] = 1 + cycle_lenght(3 * n + 1, dick)
    return dick[n]


i = 0
j = 0
dick = {}
dick[1] = 1
while True:
    maximo = 0
    line = input()
    if line is None:
        break
    it = line.find(" ")
    i = int(line[:it])
    j = int(line[it + 1:])
    for n in range(min(i, j), max(i, j) + 1):
        maximo = max(maximo, cycle_lenght(n, dick))
    print(f"{i} {j} {maximo}")


