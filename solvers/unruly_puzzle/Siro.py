def leer_tablero():
    file = open("tablero.txt", 'r')
    temp = file.read()
    n = temp.find(temp[-1])
    tablero = []
    for i in range(len(temp)):
        if temp[i] == ".":
            tablero.append(0)
        elif temp[i] == "1":
            tablero.append(1)
        elif temp[i] == "2":
            tablero.append(2)

    return tablero, n


def print_tablero(tablero, n):
    for i in range(len(tablero)):
        print(" " if tablero[i] == 0 else "*" if tablero[i] == 1 else ".", end=' ')
        if (i + 1) % n == 0:
            print()


def de_una(tablero, n):
    anterior = [tablero[i] for i in range(len(tablero))]
    two_in_a_row(tablero, n)
    same_number(tablero, n)
    while anterior != tablero:
        anterior = [tablero[i] for i in range(len(tablero))]
        two_in_a_row(tablero, n)
        same_number(tablero, n)


def two_in_a_row(tablero, n):
    for i in range(len(tablero) - 1):
        if tablero[i] != 0:
            # check horizontal
            if tablero[i] == tablero[i + 1]:
                if i % n < n - 2:
                    if tablero[i + 2] == 0:
                        tablero[i + 2] = (tablero[i] * 2) % 3
                if i % n > 0:
                    if tablero[i - 1] == 0:
                        tablero[i - 1] = (tablero[i] * 2) % 3
            if i % n < n - 2:
                if (tablero[i] == tablero[i + 2]) and (tablero[i + 1] == 0):
                    tablero[i + 1] = (tablero[i] * 2) % 3
            # check vertical
            if i < n * (n - 1):
                if tablero[i] == tablero[i + n]:
                    if i > n - 1:
                        if tablero[i - n] == 0:
                            tablero[i - n] = (tablero[i] * 2) % 3
                    if i < n * (n - 2):
                        if tablero[i + 2 * n] == 0:
                            tablero[i + 2 * n] = (tablero[i] * 2) % 3
                if i < n * (n - 2):
                    if (tablero[i] == tablero[i + 2 * n]) and (tablero[i + n] == 0):
                        tablero[i + n] = (tablero[i] * 2) % 3


def contar(tablero, n):
    row1 = [0] * n
    row2 = [0] * n
    column1 = [0] * n
    column2 = [0] * n
    for i in range(len(tablero)):
        if tablero[i] == 1:
            row1[i // n] = row1[i // n] + 1
            column1[i % n] = column1[i % n] + 1
        if tablero[i] == 2:
            row2[i // n] = row2[i // n] + 1
            column2[i % n] = column2[i % n] + 1
    return row1, row2, column1, column2


def same_number(tablero, n):
    row1, row2, column1, column2 = contar(tablero, n)
    # rellenamos filas
    for i in range(n):
        if row1[i] == n / 2:
            for j in range(n):
                if tablero[j + i * n] == 0:
                    tablero[j + i * n] = 2
                    column2[j] = column2[j] + 1
        if row2[i] == n / 2:
            for j in range(n):
                if tablero[j + i * n] == 0:
                    tablero[j + i * n] = 1
                    column1[j] = column1[j] + 1

    for i in range(n):
        if column1[i] == n / 2:
            for j in range(n):
                if tablero[j * n + i] == 0:
                    tablero[j * n + i] = 2
        if column2[i] == n / 2:
            for j in range(n):
                if tablero[j * n + i] == 0:
                    tablero[j * n + i] = 1


def check(tablero, n):
    row1, row2, column1, column2 = contar(tablero, n)
    for i in range(n):
        if row1[i] > n / 2:
            return 0
        if row2[i] > n / 2:
            return 0
        if column1[i] > n / 2:
            return 0
        if column2[i] > n / 2:
            return 0
    for i in range(len(tablero) - 2):
        if tablero[i] != 0:
            # check horizontal
            if i % n < n - 2:
                if tablero[i] == tablero[i + 1] and tablero[i] == tablero[i + 2]:
                    return 0
            # check vertical
            if i < n * (n - 2):
                if tablero[i] == tablero[i + n] and tablero[i] == tablero[i + 2 * n]:
                    return 0
    return 1


def dale(tablero, n):
    posibilidad = [tablero[i] for i in range(len(tablero))]
    de_una(posibilidad, n)
    if check(posibilidad, n) == 0:
        return 0
    if 0 in posibilidad:
        pos = posibilidad.index(0)
        posibilidad[pos] = 1

        if dale(posibilidad, n):
            return 1
        else:
            posibilidad[pos] = 2
            return dale(posibilidad, n)
    else:
        print_tablero(posibilidad, n)
        return 1


tablero, n = leer_tablero()
print_tablero(tablero, n)
print()
dale(tablero, n)


