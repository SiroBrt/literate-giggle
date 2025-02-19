def leer_tablero():
    file = open("tablero.txt", 'r')
    temp = file.read()
    num = 0
    first_read = []
    i = 0
    while (i < len(temp)):
        if temp[i].isnumeric():
            num = num * 10 + (ord(temp[i]) - ord('0'))
        elif temp[i] == ' ':
            first_read.append(num)
            num = 0
        else:
            first_read.append(num)
            num = 0
            i += 1
            break
        i += 1
    if len(first_read) % 4 != 0:
        return 0, [], []
    n = int(len(first_read) / 4)
    # Formateamos bordes como 4 arrays de izq a der, arriba a abajo
    borde = [[], [], [], []]
    count = 0
    for j in range(len(first_read)):
        borde[count].append(first_read[j])
        if j % n == n - 1:
            count += 1
    borde[2].reverse()
    borde[3].reverse()
    tablero = []
    if i == len(temp):
        tablero = [0 for i in range(n * n)]
    else:
        while (i < len(temp)):
            if temp[i].isnumeric():
                num = num * 10 + (ord(temp[i]) - ord('0'))
            elif temp[i] == ' ' or ord(temp[i]) == 10:
                tablero.append(num)
                num = 0
            else:
                first_read.append(num)
                num = 0
                break
            i += 1
        if len(tablero) != n * n:
            return 0, [], []
    return n, borde, tablero


def imprimir_tablero(n, tablero):
    for i in range(n):
        for j in range(n):
            print(tablero[j + i * n], end=' ')
        print()


def fill(n, tablero, posibilidades, pos, num):
    tablero[pos] = num
    posibilidades[pos] = []
    row = n * int(pos / n)
    col = pos % n
    for i in range(n):
        if num in posibilidades[col + n * i]:
            posibilidades[col + n * i].remove(num)
        if num in posibilidades[row + i]:
            posibilidades[row + i].remove(num)
    return


def get_it(n, pov, lado):
    match lado:
        case 0:
            it = pov
            increment = n
        case 1:
            it = n * (pov + 1) - 1
            increment = -1
        case 2:
            it = n * (n - 1) + pov
            increment = -n
        case 3:
            it = pov * n
            increment = 1
    return it, increment


def initial_advance(n, borde, tablero, posibilidades):
    # borrar los valores dados
    for i in range(n**2):
        if tablero[i] != 0:
            fill(n, tablero, posibilidades, i, tablero[i])
    # bordes faciles
    for i in range(n):
        if borde[0][i] + borde[2][i] == n + 1:
            fill(n, tablero, posibilidades, (borde[0][i] - 1) * n + i, n)
        elif borde[0][i] == 1:
            fill(n, tablero, posibilidades, i, n)
        elif borde[2][i] == 1:
            fill(n, tablero, posibilidades, n * (n - 1) + i, n)

        if borde[1][i] + borde[3][i] == n + 1:
            fill(n, tablero, posibilidades, n * i + borde[3][i] - 1, n)
        elif borde[1][i] == 1:
            fill(n, tablero, posibilidades, n * (i + 1) - 1, n)
        elif borde[3][i] == 1:
            fill(n, tablero, posibilidades, n * i, n)
    return


def vision_count(n, tablero, pov, lado):
    count = 0
    alto = 0
    it = 0
    increment = 0
    it, increment = get_it(n, pov, lado)
    for i in range(n):
        if tablero[it] > alto:
            alto = tablero[it]
            count += 1
        it += increment
    return count


def check(n, borde, tablero, posibilidades):
    for i in range(4 * n):
        if (borde[int(i / n)][i % n] != 0):
            linea = extraer_linea(n, tablero, i % n, int(i / n))
            visto = vision_count(n, tablero, i % n, int(i / n))
            hay_que_ver = borde[int(i / n)][i % n]
            if visto > hay_que_ver:
                return 0
            if 0 not in linea and visto != hay_que_ver:
                return 0
    temp = []
    for i in range(n):
        # filas distintas
        for j in range(n):
            if tablero[i * n + j] in temp:
                return 0
            if tablero[i * n + j] != 0:
                temp.append(tablero[i * n + j])
        temp.clear()
        # columnas distintas
        for j in range(n):
            if tablero[i + n * j] in temp:
                return 0
            if tablero[i + n * j] != 0:
                temp.append(tablero[i + n * j])
        temp.clear()
    for i in range(n**2):
        if tablero[i] == 0 and posibilidades[i] == []:
            return 0
    return 1


def extraer_linea(n, tablero, pov, lado):
    if lado % 2 == 0:
        linea = [tablero[pov + n * i] for i in range(n)]
    else:
        linea = [tablero[pov * n + i] for i in range(n)]
    if lado == 1 or lado == 2:
        linea.reverse()
    return linea


def grupos(n, tablero, posibilidades, pos):
    cambios = 0
    row = n * int(pos / n)
    col = pos % n
    row_counter = 0
    col_counter = 0
    for i in range(n):
        if posibilidades[row + i] == posibilidades[pos]:
            row_counter += 1
        if posibilidades[n * i + col] == posibilidades[pos]:
            col_counter += 1
    if col_counter == len(posibilidades[pos]):
        for i in range(n):
            if posibilidades[n * i + col] != posibilidades[pos]:
                for j in posibilidades[pos]:
                    if j in posibilidades[n * i + col]:
                        posibilidades[n * i + col].remove(j)
                        cambios = 1
    if row_counter == len(posibilidades[pos]):
        for i in range(n):
            if posibilidades[row + 1] != posibilidades[pos]:
                for j in posibilidades[pos]:
                    if j in posibilidades[row + 1]:
                        posibilidades[row + 1].remove(j)
                        cambios = 1
    return cambios


def subir_lower_bound(n, borde, tablero, posibilidades, pov, lado):
    cambio = 0
    it, increment = get_it(n, pov, lado)
    if borde[lado][pov] == 2 and posibilidades[it] != []:
        linea = extraer_linea(n, tablero, pov, lado)
        if n in linea:
            index = linea.index(n)
            if index > 1:
                suelo = 0
                for i in range(1, index):
                    if posibilidades[it + i * increment] == []:
                        suelo = max(suelo, tablero[it + i * increment])
                    else:
                        suelo = max(suelo, posibilidades[it + i * increment][0])
                # print(f"suelo {suelo}")
                if posibilidades[it][0] <= suelo:
                    for i in range(len(posibilidades[it])):
                        if posibilidades[it][0] <= suelo:
                            posibilidades[it].remove(posibilidades[it][0])
                            cambio = 1
                if posibilidades[it] == []:
                    return -1
                techo = posibilidades[it][-1]
                for i in range(1, index):
                    if posibilidades[it + i * increment] == []:
                        continue
                    if techo <= posibilidades[it + i * increment][-1]:
                        for j in range(techo, n):
                            if j in posibilidades[it + i * increment]:
                                posibilidades[it + i * increment].remove(j)
                                cambio = 1

    return cambio


def bajar_upper_bound(n, borde, tablero, posibilidades, pov, lado):
    cambio = 0
    if borde[lado][pov] == 0:
        return 0
    linea = extraer_linea(n, tablero, pov, lado)
    retirar = [i + 1 for i in range(n - borde[lado][pov] + 1, n)]
    retirar.reverse()
    if n in linea:
        for i in range(linea.index(n) + 1, n):
            if linea[i] in retirar:
                retirar.append(retirar[-1] - 1)
                retirar.remove(linea[i])
    it, increment = get_it(n, pov, lado)
    for i in range(len(retirar)):
        for j in range(len(retirar) - i):
            if retirar[j] in posibilidades[it + i * increment]:
                posibilidades[it + i * increment].remove(retirar[j])
                cambio = 1
    return cambio


def force_advance(n, borde, tablero, posibilidades):
    cambio = 1
    while cambio != 0:
        cambio = 0
        # trucos de tablero
        for i in range(n**2):
            if len(posibilidades[i]) == 1:
                fill(n, tablero, posibilidades, i, posibilidades[i][0])
                cambio = 1
            cambio += grupos(n, tablero, posibilidades, i)

        # trucos de bordes
        for i in range(n):
            for j in range(4):
                cambio += bajar_upper_bound(n, borde, tablero, posibilidades, i, j)
                cambio += subir_lower_bound(n, borde, tablero, posibilidades, i, j)
        #     print(vision(n, tablero, i, 1), end='')

    return


def profundidad(n, borde, tablero, posibilidades, d):
    # print(f"profundidad {d}")
    # imprimir_tablero(n, tablero)
    # imprimir_tablero(n, posibilidades)
    force_advance(n, borde, tablero, posibilidades)
    if not check(n, borde, tablero, posibilidades):
        return 0
    if 0 in tablero:
        pos = tablero.index(0)
        tablero_copy = []
        posibilidades_copy = []
        for i in range(len(posibilidades[pos])):

            tablero_copy = [j for j in tablero]
            posibilidades_copy.clear()
            for j in range(n**2):
                posibilidades_copy.append([k for k in posibilidades[j]])

            fill(n, tablero_copy, posibilidades_copy, pos, posibilidades[pos][0])
            if not profundidad(n, borde, tablero_copy, posibilidades_copy, d + 1):
                posibilidades[pos].pop(0)
            else:
                posibilidades = posibilidades_copy
                tablero = tablero_copy
                return 1
    else:
        print("encontrado")
        imprimir_tablero(n, tablero)
        return 1


def solve():
    n, borde, tablero = leer_tablero()
    posibilidades = [[] for i in range(n**2)]
    for i in posibilidades:
        for j in range(1, n + 1):
            i.append(j)
    initial_advance(n, borde, tablero, posibilidades)
    force_advance(n, borde, tablero, posibilidades)
    imprimir_tablero(n, tablero)
    if not profundidad(n, borde, tablero, posibilidades, 0):
        print("no es posible")
        return
    return


solve()
