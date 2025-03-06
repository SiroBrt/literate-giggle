def leer_tablero():
    file = open("tablero.txt", 'r')
    temp = file.read()
    size = [0, 0]
    size[0] = temp.find(temp[-1])
    tablero = []
    for i in range(len(temp)):
        if temp[i] == '.':
            tablero.append(-1)
        elif temp[i].isnumeric():
            if temp[i] == '5':
                tablero.append(5)
            else:
                tablero.append(ord(temp[i]) - ord('0'))
    size[1] = len(tablero) // size[0]
    return tablero, size


board, size = leer_tablero()


def print_tablero(tablero):
    for i in range(size[1]):
        for j in range(size[0]):
            match tablero[i * size[0] + j]:
                case 5:
                    print("#", end=" ")
                case -1:
                    print(".", end=" ")
                case -2:
                    print(" ", end=" ")
                case -3:
                    print("*", end=" ")
                case _:
                    print(tablero[i * size[0] + j], end=" ")
        print(" ")


def add_faro(tablero, n):
    tablero[n] = -3  # -3 es faro

    it = n + 1
    while it % size[0] != 0:
        if tablero[it] == -3:
            return -1
        if tablero[it] >= 0:
            break
        tablero[it] = -2  # -2 es "seguro que no hay faro"
        it += 1

    it = n - 1
    while it % size[0] != size[0] - 1:
        if tablero[it] == -3:
            return -1
        if tablero[it] >= 0:
            break
        tablero[it] = -2
        it -= 1

    it = n + size[0]
    while it < size[0] * size[1]:
        if tablero[it] == -3:
            return -1
        if tablero[it] >= 0:
            break
        tablero[it] = -2
        it += size[0]

    it = n - size[0]
    while it >= 0:
        if tablero[it] == -3:
            return -1
        if tablero[it] >= 0:
            break
        tablero[it] = -2
        it -= size[0]
    return 0


def contar_alrededor(tablero, n):
    wanted = tablero[n]
    count = 0
    hueco = []
    if n >= size[0]:
        match tablero[n - size[0]]:
            case -3:
                count += 1
            case -1:
                hueco.append(n - size[0])
    if n % size[0] != 0:
        match tablero[n - 1]:
            case -3:
                count += 1
            case -1:
                hueco.append(n - 1)
    if n % size[0] != size[0] - 1:
        match tablero[n + 1]:
            case -3:
                count += 1
            case -1:
                hueco.append(n + 1)
    if n < size[0] * (size[1] - 1):
        match tablero[n + size[0]]:
            case -3:
                count += 1
            case -1:
                hueco.append(n + size[0])
    return wanted, count, hueco


def rellenar_numero(tablero, n):
    wanted, count, hueco = contar_alrededor(tablero, n)
    if wanted < count:
        return -1
    if wanted == count:
        for i in hueco:
            if tablero[i] == -1:
                tablero[i] = -2
    elif wanted - count == len(hueco):
        for i in hueco:
            if add_faro(tablero, i) == -1:
                return -1
    elif wanted - count == len(hueco) - 1:
        for i in hueco:
            if (i + size[0] - 1) in hueco:
                pos = i - 1 + (i == n + 1) * (1 + size[0])
                if tablero[pos] == -1:
                    tablero[pos] = -2
            if (i + size[0] + 1) in hueco:
                pos = i + 1 + (i == n - 1) * (size[0] - 1)
                if tablero[pos] == -1:
                    tablero[pos] = -2
    return 0


def posibles_fuentes(tablero, n):
    lista = []
    if tablero[n] == -1:
        lista.append(n)
    it = n + 1
    while it % size[0] != 0:
        if tablero[it] >= 0:
            break
        if tablero[it] != -2:
            lista.append(it)
        it += 1

    it = n - 1
    while it % size[0] != size[0] - 1:
        if tablero[it] >= 0:
            break
        if tablero[it] != -2:
            lista.append(it)
        it -= 1

    it = n + size[0]
    while it < size[0] * size[1]:
        if tablero[it] >= 0:
            break
        if tablero[it] != -2:
            lista.append(it)
        it += size[0]

    it = n - size[0]
    while it >= 0:
        if tablero[it] >= 0:
            break
        if tablero[it] != -2:
            lista.append(it)
        it -= size[0]
    return lista


def logic(tablero):
    copia = []
    while tablero != copia:
        copia = [i for i in tablero]
        print("iteracion")
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
                            if add_faro(tablero, lista[0]) == -1:
                                return -1


# add_faro(board, 3)
# add_faro(board, 1)
# print(rellenar_numero(board, 44))
logic(board)
print_tablero(board)
# print(posibles_fuentes(board, 12))
