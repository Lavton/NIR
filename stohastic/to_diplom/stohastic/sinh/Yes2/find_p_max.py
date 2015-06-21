#!/usr/bin/python3.4
import sys
from math import exp
data = [line.strip().split() for line in open(sys.argv[1])]
for j in range(len(data)):
    data[j]=[float(i) for i in data[j]]

data = [list(y) for y in zip(*data)]
for i in range (len(data[0])):
	data[0][i]+=0.5
data = [list(y) for y in zip(*data)]
f = open('merge.txt', 'w')
for line in data:
    f.write(" ".join(((str(el) for el in line)))+"\n")