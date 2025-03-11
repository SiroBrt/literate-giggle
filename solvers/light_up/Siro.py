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


def iluminado(tablero, n):
    if tablero[n] == -3:
        return 1
    it = n + 1
    while it % size[0] != 0:
        if tablero[it] == -3:
            return 1
        if tablero[it] >= 0:
            break
        it += 1

    it = n - 1
    while it % size[0] != size[0] - 1:
        if tablero[it] == -3:
            return 1
        if tablero[it] >= 0:
            break
        it -= 1

    it = n + size[0]
    while it < size[0] * size[1]:
        if tablero[it] == -3:
            return 1
        if tablero[it] >= 0:
            break
        it += size[0]

    it = n - size[0]
    while it >= 0:
        if tablero[it] == -3:
            return 1
        if tablero[it] >= 0:
            break
        it -= size[0]
    return 0


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
    if iluminado(tablero, n):
        return [0, 0, 0]
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
        # print("iteracion")
        for i in range(len(tablero)):
            match tablero[i]:
                case 0 | 1 | 2 | 3 | 4:
                    if rellenar_numero(tablero, i) == -1:
                        return -1
                case -1 | -2:
                    lista = posibles_fuentes(tablero, i)
                    match len(lista):
                        case 0:
                            return -1
                        case 1:
                            if add_faro(tablero, lista[0]) == -1:
                                return -1


def check_alrededor(tablero, n):
    wanted, count, hueco = contar_alrededor(tablero, n)
    if count > wanted:
        return 0
    if wanted - count > len(hueco):
        return 0
    return 1


def check(tablero):
    for i in range(len(tablero)):
        match tablero[i]:
            case -3:
                tablero[i] = 0
                if iluminado(tablero, i):
                    tablero[i] = -3
                    return 0
                else:
                    tablero[i] = -3
            case 0 | 1 | 2 | 3 | 4:
                if check_alrededor(tablero, i) == 0:
                    return 0
            case -2:
                if iluminado(tablero, i) == 0 and len(posibles_fuentes(tablero, i)) == 0:
                    return 0
    return 1


def profundidad(tablero):
    logic(tablero)
    if check(tablero) == 0:
        return -1
    if -1 in tablero:
        copia = [i for i in tablero]
        it = copia.index(-1)
        add_faro(copia, it)
        if profundidad(copia) == 1:
            return 1
        else:
            tablero[it] = -2
            copia = [i for i in tablero]
            if profundidad(copia) == 1:
                return 1
            else:
                return -1
    print_tablero(tablero)
    return 1


# print(rellenar_numero(board, 44))
print_tablero(board)
print("-" * (size[0] * 2 - 1))
profundidad(board)
# print(posibles_fuentes(board, 12))
