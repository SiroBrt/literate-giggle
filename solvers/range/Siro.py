import math


def leer_tablero():
    file = open("tablero.txt", 'r')
    temp = file.read()
    size = [0, 0]
    numeros = []
    tablero = []
    num = 0
    it = 0
    counting_num = 0
    for i in temp:
        if i.isnumeric():
            num = num * 10 + (ord(i) - ord('0'))
            counting_num = 1
        elif i == '.':
            if counting_num == 1 or num != 0:
                return tablero, [-1, -1], numeros
            num = -1
        elif i == ' ':
            tablero.append(num)
            if counting_num:
                numeros.append(it)
            num = 0
            counting_num = 0
            it += 1
        elif i == temp[-1]:
            tablero.append(num)
            if counting_num:
                numeros.append(it)
            num = 0
            counting_num = 0
            it += 1
            if size[1] == 0:
                size[1] = it
    size[0] = len(tablero) // size[1]
    return tablero, size, numeros


def print_tablero(tablero, size):
    maxlen = 1 + math.floor(math.log10(max(tablero)))
    for i in range(len(tablero)):
        handicap = 0
        if tablero[i] == 1:
            print(".", end='')
        elif tablero[i] == 0:
            print("*", end='')
        elif tablero[i] == -1:
            print(" ", end='')
        else:
            print(tablero[i], end='')
            handicap = math.floor(math.log10(tablero[i]))
        print(' ' * (maxlen - handicap), end='')
        if (i + 1) % size[1] == 0:
            print()
    print()


def separar_isla(ceros, size):
    new = []
    new.append(ceros.pop(0))
    i = -1
    while (i + 1 != len(new)):
        i += 1
        # check si izq-arriba existe y es un bloque que aun no hemos añadido
        if (new[i] % size[1] != 0) and (new[i] > size[1] - 1) and (new[i] - 1 - size[1] in ceros):
            j = ceros.index(new[i] - 1 - size[1])
            new.append(ceros.pop(j))
        if ((new[i] + 1) % size[1] != 0) and (new[i] > size[1] - 1) and (new[i] + 1 - size[1] in ceros):
            j = ceros.index(new[i] + 1 - size[1])
            new.append(ceros.pop(j))
        if (new[i] % size[1] != 0) and (new[i] < (size[0] - 1) * size[1]) and (new[i] - 1 + size[1] in ceros):
            j = ceros.index(new[i] - 1 + size[1])
            new.append(ceros.pop(j))
        if ((new[i] + 1) % size[1] != 0) and (new[i] < (size[0] - 1) * size[1]) and (new[i] + 1 + size[1] in ceros):
            j = ceros.index(new[i] + 1 + size[1])
            new.append(ceros.pop(j))
    return new


def check_loops(tablero, size):  # 1 si encuentra loops, 0 si no
    ceros = []
    for i in range(len(tablero)):
        if tablero[i] == 0:
            ceros.append(i)
    islas = []
    while (len(ceros) != 0):
        islas.append(separar_isla(ceros, size))
    for isla_actual in islas:
        if len(isla_actual) == 1:
            continue
        borde = 0
        for i in isla_actual:
            if (i % size[1] == 0) or ((i + 1) % size[1] == 0) or (i >= (size[0] - 1) * size[1]) or (i <= size[1] - 1):
                borde += 1
                if borde == 2:
                    return 1
        visitados = []
        por_visitar = [isla_actual[0]]
        while (len(por_visitar) != 0):
            # print("por visitar: ", por_visitar, "visitados: ", visitados)
            count = 0
            if (por_visitar[0] % size[1] != 0) and (por_visitar[0] > size[1] - 1) and (por_visitar[0] - 1 - size[1] in isla_actual):
                if por_visitar[0] - 1 - size[1] in visitados:
                    count += 1
                else:
                    if por_visitar[0] - 1 - size[1] not in por_visitar:
                        por_visitar.append(por_visitar[0] - 1 - size[1])
            if ((por_visitar[0] + 1) % size[1] != 0) and (por_visitar[0] > size[1] - 1) and (por_visitar[0] + 1 - size[1] in isla_actual):
                if por_visitar[0] + 1 - size[1] in visitados:
                    count += 1
                else:
                    if por_visitar[0] + 1 - size[1] not in por_visitar:
                        por_visitar.append(por_visitar[0] + 1 - size[1])
            if (por_visitar[0] % size[1] != 0) and (por_visitar[0] < (size[0] - 1) * size[1]) and (por_visitar[0] - 1 + size[1] in isla_actual):
                if por_visitar[0] - 1 + size[1] in visitados:
                    count += 1
                else:
                    if por_visitar[0] - 1 + size[1] not in por_visitar:
                        por_visitar.append(por_visitar[0] - 1 + size[1])
            if ((por_visitar[0] + 1) % size[1] != 0) and (por_visitar[0] < (size[0] - 1) * size[1]) and (por_visitar[0] + 1 + size[1] in isla_actual):
                if por_visitar[0] + 1 + size[1] in visitados:
                    count += 1
                else:
                    if por_visitar[0] + 1 + size[1] not in por_visitar:
                        por_visitar.append(por_visitar[0] + 1 + size[1])
            visitados.append(por_visitar.pop(0))
            if count > 1:
                return 1

    return 0


def check_espacio(tablero, size, i):
    # cuenta cuantas casillas hay disponibles hacia cada
    # lado y cuantas de ellas están conectadas
    count = [1, 1]
    # contamos la horizontal hacia la izq
    if i % size[1] != 0:
        pos = i - 1
        marcado = 1
        while (tablero[pos] != 0):
            count[0] += 1
            marcado = marcado * (1 - (tablero[pos] == -1))
            count[1] += marcado
            if pos % size[1] != 0:
                pos = pos - 1
            else:
                break
    # contamos la horizontal hacia la derecha
    if (i + 1) % size[1] != 0:
        pos = i + 1
        marcado = 1
        while (tablero[pos] != 0):
            count[0] += 1
            marcado = marcado * (1 - (tablero[pos] == -1))
            count[1] += marcado
            if (pos + 1) % size[1] != 0:
                pos += 1
            else:
                break

    # contamos la vertical hacia arriba
    if i > size[1] - 1:
        pos = i - size[1]
        marcado = 1
        while (tablero[pos] != 0):
            count[0] += 1
            marcado = marcado * (1 - (tablero[pos] == -1))
            count[1] += marcado
            if pos > size[1] - 1:
                pos = pos - size[1]
            else:
                break
    # contamos la vertical hacia abajo
    if i < (size[0] - 1) * size[1]:
        pos = i + size[1]
        marcado = 1
        while (tablero[pos] != 0):
            count[0] += 1
            marcado = marcado * (1 - (tablero[pos] == -1))
            count[1] += marcado
            if pos < (size[0] - 1) * size[1]:
                pos = pos + size[1]
            else:
                break
    return count


def bloquear(tablero, size, i):
    # pone un 0 en i y lo rodea de 1s
    tablero[i] = 0
    if i % size[1] != 0:
        if tablero[i - 1] == -1:
            tablero[i - 1] = 1
    if (i + 1) % size[1] != 0:
        if tablero[i + 1] == -1:
            tablero[i + 1] = 1
    if i > size[1] - 1:
        if tablero[i - size[1]] == -1:
            tablero[i - size[1]] = 1
    if i < (size[0] - 1) * size[1]:
        if tablero[i + size[1]] == -1:
            tablero[i + size[1]] = 1

    return


def check(tablero, size):
    if check_loops(tablero, size):
        return 0
    temp = []
    for i in range(len(tablero)):
        if tablero[i] > 1:
            temp = check_espacio(tablero, size, i)
            if temp[0] < tablero[i] or temp[1] > tablero[i]:
                return 0
        elif tablero[i] == 0:
            if (i + 1) % size[1] != 0:
                if tablero[i + 1] == 0:
                    return 0
            if i < (size[0] - 1) * size[1]:
                if tablero[i + size[1]] == 0:
                    return 0
    return 1


def encontrar_tope(tablero, size, i):
    der = i
    izq = i
    abajo = i
    arriba = i
    while (izq % size[1] != 0):
        izq = izq - 1
        if tablero[izq] < 1:
            break
    while ((der + 1) % size[1] != 0):
        der += 1
        if tablero[der] < 1:
            break
    while (arriba > size[1] - 1):
        arriba = arriba - size[1]
        if tablero[arriba] < 1:
            break
    while (abajo < (size[0] - 1) * size[1]):
        abajo = abajo + size[1]
        if tablero[abajo] < 1:
            break
    return izq, der, arriba, abajo


def poner_topes(tablero, size, i):
    izq, der, arriba, abajo = encontrar_tope(tablero, size, i)
    if izq != i and tablero[izq] == -1:
        bloquear(tablero, size, izq)
    if der != i and tablero[der] == -1:
        bloquear(tablero, size, der)
    if arriba != i and tablero[arriba] == -1:
        bloquear(tablero, size, arriba)
    if abajo != i and tablero[abajo] == -1:
        bloquear(tablero, size, abajo)
    return


def rellenar(tablero, size, i):
    pos = i
    while (pos % size[1] != 0):
        pos = pos - 1
        if tablero[pos] == 0:
            break
        elif tablero[pos] == -1:
            tablero[pos] = 1
    pos = i
    while ((pos + 1) % size[1] != 0):
        pos += 1
        if tablero[pos] == 0:
            break
        elif tablero[pos] == -1:
            tablero[pos] = 1
    pos = i
    while (pos > size[1] - 1):
        pos = pos - size[1]
        if tablero[pos] == 0:
            break
        elif tablero[pos] == -1:
            tablero[pos] = 1
    pos = i
    while (pos < (size[0] - 1) * size[1]):
        pos = pos + size[1]
        if tablero[pos] == 0:
            break
        elif tablero[pos] == -1:
            tablero[pos] = 1
    return


def extender_cruz(tablero, size, i):
    espacio = check_espacio(tablero, size, i)
    if espacio[1] == tablero[i]:
        poner_topes(tablero, size, i)
        return
    if espacio[0] == tablero[i]:
        rellenar(tablero, size, i)
        return
    izq, der, arriba, abajo = encontrar_tope(tablero, size, i)
    # extender derecha
    if der != i and tablero[der] == -1:
        tablero[der] = 0
        check0 = check(tablero, size)
        tablero[der] = 1
        check1 = check(tablero, size)
        if check0 and check1:
            tablero[der] = -1
        elif check1:
            tablero[der] = 1
        elif check0:
            bloquear(tablero, size, der)
        else:
            return -1
    # extender izquierda
    if izq != i and tablero[izq] == -1:
        tablero[izq] = 0
        check0 = check(tablero, size)
        tablero[izq] = 1
        check1 = check(tablero, size)
        if check0 and check1:
            tablero[izq] = -1
        elif check1:
            tablero[izq] = 1
        elif check0:
            bloquear(tablero, size, izq)
        else:
            return -1
    # extender arriba
    if arriba != i and tablero[arriba] == -1:
        tablero[arriba] = 0
        check0 = check(tablero, size)
        tablero[arriba] = 1
        check1 = check(tablero, size)
        if check0 and check1:
            tablero[arriba] = -1
        elif check1:
            tablero[arriba] = 1
        elif check0:
            bloquear(tablero, size, arriba)
        else:
            return -1
    # extender abajo
    if abajo != i and tablero[abajo] == -1:
        tablero[abajo] = 0
        check0 = check(tablero, size)
        tablero[abajo] = 1
        check1 = check(tablero, size)
        if check0 and check1:
            tablero[abajo] = -1
        elif check1:
            tablero[abajo] = 1
        elif check0:
            bloquear(tablero, size, abajo)
        else:
            return -1
    return


def avanzar(tablero, size, numeros):
    temp1 = [i for i in tablero]
    for i in numeros:
        temp2 = [j for j in temp1]
        extender_cruz(tablero, size, i)
        while (tablero != temp2):
            temp2 = [j for j in tablero]
            extender_cruz(tablero, size, i)
    while (temp1 != tablero):
        temp1 = [j for j in tablero]
        for i in numeros:
            temp2 = [j for j in temp1]
            extender_cruz(tablero, size, i)
            while (tablero != temp2):
                temp2 = [j for j in tablero]
                extender_cruz(tablero, size, i)


def solve(tablero, size, numeros):
    posibilidad = [tablero[i] for i in range(len(tablero))]
    avanzar(posibilidad, size, numeros)
    if check(posibilidad, size) == 0:
        return 0
    if -1 in posibilidad:
        pos = posibilidad.index(-1)
        posibilidad[pos] = 1
        if solve(posibilidad, size, numeros):
            return 1
        else:
            bloquear(posibilidad, size, pos)
            return solve(posibilidad, size, numeros)
    else:
        print_tablero(posibilidad, size)
        return 1


tablero, size, numeros = leer_tablero()
if size[0] != -1:
    print("" if solve(tablero, size, numeros) else "no solution found")

