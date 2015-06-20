#!/usr/bin/python3.4
import sys
from functools import reduce

print (sys.argv)
dates = []
for i in range(1, len(sys.argv), 2):
    data = [line.strip().split() for line in open(sys.argv[i])]
    for j in range(len(data)):
        data[j]=[float(data[j][0]), float(data[j][int(sys.argv[i+1])+1])]
    dates.append(data)

def avar(data, ind):
    res = []
    for i in range(1, len(data[ind])):
        if ind:
            res.append((data[ind][i]+data[ind-1][i])/2)
        else:
            res.append(data[ind][i])
    return res

def mergeTwo(data1, data2):
    merge_data = []
    it1 = 0
    it2 = 0
    while (it1 < len(data1)) and (it2 < len(data2)):
        if data1[it1] > data2[it2]:
            merge_data.append([data2[it2][0]]+avar(data1, it1)+data2[it2][1:])
            it2 += 1
        elif data1[it1] < data2[it2]:
            merge_data.append([data1[it1][0]]+data1[it1][1:]+avar(data2, it2))
            it1 += 1
        else:
            merge_data.append([data1[it1][0]]+data1[it1][1:]+data2[it2][1:])
            it1 += 1
            it2 += 1
    return merge_data

merge_data = reduce(mergeTwo, dates)

f = open('merge.txt', 'w')
for line in merge_data:
    f.write(" ".join(((str(el) for el in line)))+"\n")