list1 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 7]
list2 = [list1[i] for i in range(len(list1))]
list2[3] = 0
print(list1)
