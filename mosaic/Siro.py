def leer_tablero():
    file = open("tablero.txt", 'r')
    temp = file.read()
    size = [0, 0]
    size[1] = temp.find(temp[-1])
    tablero = []
    for i in range(len(temp)):
        if temp[i] == ".":
            tablero.append(-1)
        elif temp[i].isnumeric():
            tablero.append(ord(temp[i]) - ord('0'))
    size[0] = len(tablero) // size[1]
    return tablero, size


def print_tablero(tablero, size):
    for i in range(len(tablero)):
        print(" " if tablero[i] == -1 else tablero[i], end=' ')
        if (i + 1) % size[1] == 0:
            print()


def print_solution(tablero, size):
    for i in range(len(tablero)):
        print("*" if tablero[i] == 1 else " " if tablero[i] == 0 else "?", end=' ')
        if (i + 1) % size[1] == 0:
            print()


def contar_num(solution, size, i, num):
    result = (solution[i] == num)
    if i % size[1] != 0:
        result += (solution[i - 1] == num)
    if i % size[1] != size[1] - 1:
        result += (solution[i + 1] == num)
    if i > size[1] - 1:
        result += (solution[i - size[1]] == num)
        if i % size[1] != 0:
            result += (solution[i - size[1] - 1] == num)
        if i % size[1] != size[1] - 1:
            result += (solution[i - size[1] + 1] == num)
    if i < (size[0] - 1) * size[1]:
        result += (solution[i + size[1]] == num)
        if i % size[1] != 0:
            result += (solution[i + size[1] - 1] == num)
        if i % size[1] != size[1] - 1:
            result += (solution[i + size[1] + 1] == num)
    return result


def contar_entorno(tablero, size, i):
    result = 1
    if i % size[1] != 0:
        result += 1
    if i % size[1] != size[1] - 1:
        result += 1
    if i > size[1] - 1:
        result += 1
        if i % size[1] != 0:
            result += 1
        if i % size[1] != size[1] - 1:
            result += 1
    if i < (size[0] - 1) * size[1]:
        result += 1
        if i % size[1] != 0:
            result += 1
        if i % size[1] != size[1] - 1:
            result += 1
    return result


def rellenar(solution, size, i, num):
    if i > size[1] - 1:
        if solution[i - size[1]] == -1:
            solution[i - size[1]] = num
        if i % size[1] != 0 and solution[i - size[1] - 1] == -1:
            solution[i - size[1] - 1] = num
        if i % size[1] != size[1] - 1 and solution[i - size[1] + 1] == -1:
            solution[i - size[1] + 1] = num
    if i % size[1] != 0 and solution[i - 1] == -1:
        solution[i - 1] = num
    if solution[i] == -1:
        solution[i] = num
    if i % size[1] != size[1] - 1 and solution[i + 1] == -1:
        solution[i + 1] = num
    if i < (size[0] - 1) * size[1]:
        if solution[i + size[1]] == -1:
            solution[i + size[1]] = num
        if i % size[1] != 0 and solution[i + size[1] - 1] == -1:
            solution[i + size[1] - 1] = num
        if i % size[1] != size[1] - 1 and solution[i + size[1] + 1] == -1:
            solution[i + size[1] + 1] = num


def easy(tablero, size, solution):
    for i in range(len(tablero)):
        countfree = contar_num(solution, size, i, -1)
        if countfree == 0:
            continue
        entorno = contar_entorno(tablero, size, i)
        if entorno == tablero[i]:
            rellenar(solution, size, i, 1)
        count1 = contar_num(solution, size, i, 1)
        count0 = entorno - countfree - count1
        if count1 == tablero[i]:
            rellenar(solution, size, i, 0)
        elif count0 == entorno - tablero[i]:
            rellenar(solution, size, i, 1)


def avanzar(tablero, size, solution):
    temp = [i for i in solution]
    easy(tablero, size, solution)
    while (temp != solution):
        temp = [i for i in solution]
        easy(tablero, size, solution)


def check(tablero, size, solution):
    for i in range(len(tablero)):
        if tablero[i] != -1:
            entorno = contar_entorno(solution, size, i)
            count0 = contar_num(solution, size, i, 0)
            count1 = contar_num(solution, size, i, 1)
            if count1 > tablero[i]:
                return 0
            if count0 > entorno - tablero[i]:
                return 0
    return 1


def prueba(tablero, size, solution):
    avanzar(tablero, size, solution)
    if not check(tablero, size, solution):
        return 0
    posibilidad = [i for i in solution]
    if -1 in posibilidad:
        pos = posibilidad.index(-1)
        posibilidad[pos] = 0
        if prueba(tablero, size, solution):
            return 1
        else:
            posibilidad[pos] = 2
            return prueba(tablero, size, solution)
    return 1


def solve(tablero, size):
    solution = [-1 for i in range(len(tablero))]
    avanzar(tablero, size, solution)
    if prueba(tablero, size, solution):
        print_solution(solution, size)
    else:
        print("no solution found")


tablero, size = leer_tablero()
print_tablero(tablero, size)
solve(tablero, size)



