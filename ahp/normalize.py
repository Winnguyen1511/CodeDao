import numpy as np
n = 3
mat = [[1, 0.5, 3], [2, 1, 4], [1/3, 1/4, 1]]
mat = np.array(mat)
n = mat.shape[0]

sum_col = [np.sum(mat[:, i]) for i in range(0, n)]

normalize_mat = mat / sum_col

print('Step1: normalize mat=', normalize_mat)

sum_row = [[np.sum(normalize_mat[i, :])] for i in range(0, n)]
print('Step2: Sum all rows=', sum_row)
tmp_sum = np.sum(sum_row)
w = sum_row / tmp_sum
print('Step3: weight=', w)