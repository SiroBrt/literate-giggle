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
        print(tablero[i] if tablero[i] != 0 else ".", end=' ')
        if (i + 1) % n == 0:
            print()


def two_in_a_row(tablero, n):
    for i in range(len(tablero) - 1):
        if tablero[i] != 0:
            # check horizontal
            if tablero[i] == tablero[i + 1]:
                if i % n < n - 2:
                    tablero[i + 2] = (tablero[i] * 2) % 3
                if i % n > 0:
                    tablero[i - 1] = (tablero[i] * 2) % 3
            if i % n < n - 2:
                if tablero[i] == tablero[i + 2]:
                    tablero[i + 1] = (tablero[i] * 2) % 3
            # check vertical
            if i < n * (n - 1):
                if tablero[i] == tablero[i + n]:
                    if i > n - 1:
                        tablero[i - n] = (tablero[i] * 2) % 3
                    if i < n * (n - 2):
                        tablero[i + 2 * n] = (tablero[i] * 2) % 3
                if i < n * (n - 2):
                    if tablero[i] == tablero[i + 2 * n]:
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
    # rellenamos si se puede
    if (n / 2) in row1:
        shift = row1.index(n / 2) * n
        for i in range(n):
            if tablero[i + shift] == 0:
                tablero[i + shift] = 2
    if (n / 2) in row2:
        shift = row2.index(n / 2) * n
        for i in range(n):
            if tablero[i + shift] == 0:
                tablero[i + shift] = 1
    if (n / 2) in column1:
        shift = column1.index(n / 2)
        for i in range(n):
            if tablero[i * n + shift] == 0:
                tablero[i * n + shift] = 2
    if (n / 2) in column2:
        shift = column2.index(n / 2)
        for i in range(n):
            if tablero[i * n + shift] == 0:
                tablero[i * n + shift] = 1


def deducciones(tablero, n):
    row1, row2, column1, column2 = contar(tablero, n)
    backup = [tablero[i] for i in range(len(tablero))]
    for i in range(n):
        if row1[i] == n - 1:
            tablero.index()


tablero, n = leer_tablero()
for i in range(10):
    two_in_a_row(tablero, n)
    same_number(tablero, n)
print_tablero(tablero, n)


