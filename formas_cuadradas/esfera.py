import math


def coordenadas(r):
    x = 0
    y = math.floor(r)
    r2 = r**2
    result = []
    while x <= y:
        result.append([x, y])
        x += 1
        if x**2 + y**2 > r2:
            y -= 1
    return result


def dibujar_circulo(r):
    lista = coordenadas(r)

    # duplicamos este octavo de circulo para tener un cuarto
    length = len(lista)
    for i in range(length):
        if lista[length - i - 1][1] != lista[length - i - 1][0]:
            lista.append([lista[length - i - 1][1], lista[length - i - 1][0]])

    # hacemos un array con las posiciones que nos dicen
    pseudo_r = math.floor(r)
    linea = [0 for i in range(2 * pseudo_r + 1)]
    pila = []
    it = 0
    for i in range(pseudo_r):
        while lista[it][1] == pseudo_r - i:
            linea[pseudo_r + lista[it][0]] = 1
            linea[pseudo_r - lista[it][0]] = 1
            it += 1
        # transformar a string bonita
        string = ''
        for j in range(len(linea)):
            if linea[j] == 0:
                string = string + '  '
            else:
                string = string + 'X '
        pila.append(string)
        print(string)

    if pseudo_r != 0:
        print('X ' * pseudo_r + '0 ' + 'X ' * pseudo_r)     # linea central
    else:
        print('0 ')

    for i in range(len(pila)):
        print(pila.pop(-1))


def esfera(radio):
    r2 = radio**2
    pseudo_r = math.floor(radio) + 1
    num = 0
    for i in range(pseudo_r):
        print(f"\nCapa {i+1}:")
        num = math.sqrt(r2 - i**2)
        dibujar_circulo(num)


radio = float(input("radio = "))
esfera(radio)
