longitud = 4
num = '1011'
result = sorted(num)
print(result)
igual = True
for i in range(longitud):
    if result[i] != num[i]:
        igual = False
print("son iguales" if igual else "son distintos")
