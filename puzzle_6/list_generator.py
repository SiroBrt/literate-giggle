import random
import bisect

l1 = []
l2 = []
n = 1000
cambio = random.randint(0, n - 1)

for i in range(cambio):
    bisect.insort(l1, random.randint(0, 100))
for i in range(n - cambio):
    bisect.insort(l2, random.randint(-100, -1))
l2.reverse()

l3 = l1 + l2
with open("list.txt", "w") as f:
    for i in l3:
        f.write(f"{i}\n")
