# Datos iniciales. No hay validación de input
p = [3, 10, 5]
r = [2, 4, 4]

n = r[0]
sumando = p[0]
for i in range(1, len(p)):
    while (n % p[i] != r[i]):
        n = n + sumando
    sumando = sumando * p[i]
print("para las tuplas p = ", p, "r = ", r, ", n sería ", n)
