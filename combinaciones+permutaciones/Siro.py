# me das una listan y te devuelvo una lista con todas las posibles combinaciones de k elementos de la lista
def comb(n: list, k: int):
    if not n or k == 0:
        return []
    result = []
    for index, item in enumerate(n):
        if index > len(n) - k:
            break
        sub = comb(n[1 + index:], k - 1)
        if not sub:
            result.append([item])
        else:
            for icomb in sub:
                result.append([item] + icomb)
    return result


def mover(n: list):
    if len(n) == 1:
        return n
    result = []
    for i in range(len(n)):
        elem = n.copy()
        aux = elem.pop(i)
        for j in mover(elem):
            result.append(aux + j)
    return result


def perm(n: list, k: int):
    combinaciones = comb(n, k)  # hacemos las combinaciones
    result = []
    for elem in combinaciones:
        for i in mover(elem):
            result.append(i)
    return result


lista = ["a", "b", "c", "d", "e", "f", "g"]
result = perm(lista, 4)
print(f"permutaciones: {len(result)}", result)
