#!/usr/bin/python3.4
import sys
from math import exp
data = [line.strip().split() for line in open(sys.argv[1])]
for j in range(len(data)):
    data[j]=[float(data[j][0]), float(data[j][int(sys.argv[2])+1])]

data = [list(y) for y in zip(*data)]
maximum = max(data[1][1:])
print (data[1])
print (maximum)
f_max = maximum/exp(1)
print (f_max)
for i in range(len(data[1])-2, 1, -1):
    if data[1][i-1] >= f_max >= data[1][i]:
        print ("Pmax={}".format(data[0][i]))
