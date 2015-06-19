#!/usr/bin/python
import numpy as np
import pylab as pl
import subprocess
from math import *
date = [line.strip().split() for line in open("ito.out")]
x = [float(date[i][0]) for i in xrange(len(date))]
u = [float(date[i][1]) for i in xrange(len(date))]

his = np.histogram(u, bins=100, range=(-0.5, 8))
ords = []
for i in xrange(len(his[0])):
	pass
	# if 0<his[1][i+1]<6:
		# pass
	his[0][i]  *= exp(his[1][i])
	if his[0][i] != 0:
		# print his[0][i], np.log10(his[0][i])
		# his[0][i] = np.log10(his[0][i]+0.0)+0.0
		ords.append(np.log10(his[0][i]))
		# print ords[i]
	else:
		ords.append(0)
	his[1][i] = np.log10(exp(his[1][i]))
	# his[0][i] = np.log10(his[0][i])
	# if his[0][i] > 7000:
		# his[0][i] = 7000
his[1][-1] = np.log10(exp(his[1][-1]))

# print his[1]
# print ords
# pl.clf()
# pl.plot(his[1][1:], ords)
# pl.xlabel('log10(p)')
# pl.ylabel('log10(f(p))')
# pl.gca() #.set_xscale("log")
# pl.show()

new_y = []
new_x = []
for i in xrange(0,len(ords)):
	if ords[i]:
		new_x.append(his[1][i+1])
		new_y.append(ords[i])

def running_avg(inp, window):
	if not (window % 2):
		window += 1
	hw=(window-1)/2
	res = []
	res.append(inp[0])
	n = len(inp)
	for i in xrange(1,len(inp)):
		init_sum = 0.0
		if i < hw:
			k1=0
			k2=2*i
			z=k2+1
		elif (i+hw)>(n-1):
			k1=i-n+i+1
			k2=n-1
			z=k2-k1+1
		else:
			k1=i-hw
			k2=i+hw
			z=window
		for j in xrange(k1, k2+1):
			init_sum += inp[j]
		res.append(init_sum/z)
	return res


ever = running_avg(ords, 7)
f = open('output', 'w')
disp_a = []
for i in xrange(0,len(ords)):
	disp = (ords[i]-ever[i])**2
	if disp:
		disp_a.append(disp)
	f.write("{} {} {} {}\n".format(his[1][i+1], ords[i], ever[i], disp))

disp_a.sort()
print(disp_a[len(disp_a)/2])

if (disp_a[len(disp_a)/2] < 0.004):
	subprocess.call(["./killing.sh"])


# for i in xrange(len(h[0])):
# 	h[0][i] *= exp(h[1][i]*2)
# maxi = 0
# for i in xrange(len(hx[0])):
# 	if hx[1][i] > 0:
# 		maxi = i
# 		break

# right_u = [u[i] for i in xrange(len(u)) if hx[1][maxi]<=x[i]<=hx[1][maxi+1]]
# pl.clf()
# hu = pl.hist(right_u, bins=20)
# pl.gca() #.set_xscale("log")
# pl.show()

# for i in xrange(len(hu[0])):
#  	hu[0][i] *= exp(hu[1][i]*2)

# pl.clf()
# pl.plot(hu[1][1:], hu[0])
# pl.gca() #.set_xscale("log")
# pl.show()
