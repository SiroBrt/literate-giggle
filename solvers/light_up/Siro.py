def leer_tablero():
    file = open("tablero.txt", 'r')
    temp = file.read()
    size = [0, 0]
    size[0] = temp.find(temp[-1])
    tablero = []
    for i in range(len(temp)):
        if temp[i] == ".":
            tablero.append(-1)
        elif temp[i].isnumeric():
            tablero.append(ord(temp[i]) - ord('0'))
    size[1] = len(tablero) // size[0]
    return tablero, size


board, size = leer_tablero()
print(size)


def print_tablero(tablero):
    for i in range(size[1]):
        for j in range(size[0]):
            match tablero[i * size[0] + j]:
                case -1:
                    print(".", end=" ")
                case 5:
                    print("*", end=" ")
                case 6:
                    print(" ", end=" ")
                case _:
                    print(tablero[i * size[0] + j], end=" ")
        print(" ")


def add_faro(tablero, n):
    tablero[n] = 5  # 5 es faro

    it = n + 1
    while it % size[0] != 0:
        if tablero[it] == 5:
            return -1
        if tablero[it] != -1 and tablero[it] != 6:
            break
        tablero[it] = 6  # 6 es "seguro que no hay faro"
        it += 1

    it = n - 1
    while it % size[0] != size[0] - 1:
        if tablero[it] == 5:
            return -1
        if tablero[it] != -1 and tablero[it] != 6:
            break
        tablero[it] = 6
        it -= 1

    it = n + size[0]
    while it < size[0] * size[1]:
        if tablero[it] == 5:
            return -1
        if tablero[it] != -1 and tablero[it] != 6:
            break
        tablero[it] = 6
        it += size[0]

    it = n - size[0]
    while it >= 0:
        if tablero[it] == 5:
            return -1
        if tablero[it] != -1 and tablero[it] != 6:
            break
        tablero[it] = 6
        it -= size[0]
    return 0


def rellenar_numero(tablero, n):
    wanted = tablero[n]
    count = 0
    hueco = []
    if n >= size[0]:
        match tablero[n - size[0]]:
            case 5:
                count += 1
            case -1:
                hueco.append(n - size[0])
    if n % size[0] != 0:
        match tablero[n - 1]:
            case 5:
                count += 1
            case -1:
                hueco.append(n - 1)
    if n % size[0] != size[0] - 1:
        match tablero[n + 1]:
            case 5:
                count += 1
            case -1:
                hueco.append(n + 1)
    if n < size[0] * (size[1] - 1):
        match tablero[n + size[0]]:
            case 5:
                count += 1
            case -1:
                hueco.append(n + size[0])

    if count == wanted:
        for i in hueco:
            if tablero[i] == -1:
                tablero[i] = 6
        return 0
    if wanted - count == len(hueco):
        for i in hueco:
            if add_faro(tablero, i) == -1:
                return -1
    return 0


def posibles_fuentes(tablero, n):
    lista = []
    return lista


def logic(tablero):
    for i in range(len(tablero)):
        match tablero[i]:
            case 0 | 1 | 2 | 3 | 4:
                if rellenar_numero(tablero, i) == -1:
                    return -1
            case -1:
                lista = posibles_fuentes(tablero, i)
                match len(lista):
                    case 0:
                        return -1
                    case 1:
                        if rellenar_numero(tablero, lista[0]) == -1:
                            return -1


# add_faro(board, 5)
# add_faro(board, 1)
# print(rellenar_numero(board, 2))
logic(board)
print_tablero(board)
