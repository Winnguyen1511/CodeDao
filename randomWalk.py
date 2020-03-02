import random
from math import *
from decimal import *
def random_walk(n):#number of steps(blocks) in a walk
    x, y = 0, 0
    for i in range(0, n):
        [dx, dy] = random.choice([[0, 1], [1, 0],[0, -1], [-1, 0]])
        x = x + dx
        y = y + dy
    return [x, y]


no_transport_limit = 3
number_of_walk = 100000
print("Len\t per\t min\t mea\t max")
for walk_length in range(1, 100):
    no_transport = 0
    total_dist = 0
    min , max = 0, 0
    for i in range(0, number_of_walk):
        cordinate = random_walk(walk_length)
        distsq = cordinate[0]**2 + cordinate[1]**2
        dist = sqrt(distsq)
        if(min == 0 ):
            min = dist
        if(max == 0):
            max = dist
        if( min > dist):
            min = dist
        if(max < dist):
            max = dist
        total_dist += dist
        if distsq <= no_transport_limit**2:
            no_transport+=1
    total_dist /= number_of_walk
    percentage = (float(no_transport) / number_of_walk )*100
    # walk_length =  Decimal(walk_length)
    # percentage = Decimal(percentage)
    # total_dist = Decimal(total_dist)
    # min = Decimal(min)
    # max = Decimal(max)
    # getcontext().prec = 2
    prec = 2
    print(round(walk_length,prec), "\t",round(percentage,prec),
              "\t", round(min, prec),"\t", round(total_dist, prec), "\t", round(max, prec))
