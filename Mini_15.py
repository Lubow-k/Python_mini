import foreign

m1 = [[1.0, 2.0], [3.0, 4.0]]
m2 = foreign.matrix_power(m1, 3)
del m1
print(m2)
