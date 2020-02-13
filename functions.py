def swap(a, b):
    tmp = a
    a = b
    b = tmp
    print(a, b)
a = 1; b = 4

swap(a, b)
swap(b = 5, a=8)

print(a, b)
#keyword argument

print("Test keyword argument:")
def transmit(buffer, size, *, timeout=0xFF):
    print("Transmiting...")
    for i in range(0, size):
        print(buffer[i], end='')
    print('\n', end ='')
    print("timeout=", timeout)
str = "khoanguyen1511"
transmit(str, len(str))
#transmit(str, timeout=100)
print("Test packing argument with *:")

def create_list(*args):
    return list(args)

tmp = create_list(1,2,3,4,5,6)
print(tmp)

print("Test unpacking with *:")
def create_matrix(start, row, col):
    mat=[]
    for i in range(0, row):
        rows = [ start + val for val in range(0, col)]
        start = rows[col-1] + 1
        mat.append(rows)
    return mat
argv = [1,3,4]
myMat = create_matrix(*argv)
print(*myMat, sep='\n')

print("Spiral matrix:")
def creat_spiral_matrix(n, turn=0):
    dx, dy = 1, 0
    if turn == 0:
        dx, dy = 0,1
    x, y = 0,0
    spiral_matrix = [[None] * n for j in range(n)]
    for i in range(n ** 2):
        spiral_matrix[x][y] = i
        nx, ny = x + dx, y + dy
        if 0 <= nx < n and 0 <= ny < n and spiral_matrix[nx][ny] == None:
            x, y = nx, ny
        else:
            if turn == 0:
                dx, dy = dy, -dx
            else:
                dx, dy = -dy, dx
            x, y = x + dx, y + dy
    return spiral_matrix

sm = creat_spiral_matrix(5, 1)
print(*sm, sep='\n')


