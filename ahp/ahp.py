import numpy as np

mat = [[1, 0.5, 3], [2, 1, 4], [1/3, 1/4, 1]]
# w = [[0.32], [0.56], [0.12]]

mat = np.array(mat)
# w = np.array(w)
n = mat.shape[0]

sum_col = [np.sum(mat[:, i]) for i in range(0, n)]

normalize_mat = mat / sum_col

print('Step1: normalize mat=', normalize_mat)

sum_row = [[np.sum(normalize_mat[i, :])] for i in range(0, n)]
print('Step2: Sum all rows=', sum_row)
tmp_sum = np.sum(sum_row)
w = sum_row / tmp_sum
print('Step3: weight=', w)
w_vec = mat.dot(w)
print('Step1: Weight vector=',w_vec)

consistent_vec = w_vec / w
print('Step2: Consistent vect=', consistent_vec)

# n = len(consistent_vec)
lambda_max = np.sum(consistent_vec) / n

print('Step3: lamda_max=', lambda_max)

CI = (lambda_max - n)/ (n -1)
print('Step4: CI=', CI)
RI = 0.52
CR = CI / RI
print('Step5: CR = ',CR)