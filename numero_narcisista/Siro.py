limit = 25


def potencias(tabla):
    for i in range(8):
        tabla.append([i + 2])

    for i in range(8):
        num = i + 2
        for j in range(limit - 1):
            tabla[i].append(tabla[i][j] * num)


def check_narcisismo(tabla, narcisistas, num):
    result = 0
    longitud = len(num)
    for i in num:
        if i == '1':
            result += 1
        elif i != '0':
            index = int(i) - 2
            result += tabla[index][longitud - 1]
    digits = sorted(str(result))
    if len(digits) != longitud:
        return
    same = True
    for i in range(longitud):
        if digits[i] != num[i]:
            same = False
    if same:
        print(result)           # Si no hay que imprimir, quitar esto
        narcisistas.append(result)
    return


def combinaciones():
    narcisistas = [0]
    tabla = []
    potencias(tabla)
    num = '0' * limit
    while num != '9' * limit:
        if len(num) < limit:
            num = num + num[-1]
        else:
            while num[-1] == '9':
                num = num[:-1]
            digit = int(num[-1]) + 1
            num = num[:-1] + str(digit)
        check_narcisismo(tabla, narcisistas, num)
    return narcisistas


narcisistas = sorted(combinaciones())
