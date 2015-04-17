#!/usr/bin/python
import numpy as np
import pylab as pl
from math import log, exp
date = [line.strip().split() for line in open("ito.out")]
x = [float(date[i][0]) for i in xrange(len(date))]
u = [float(date[i][1]) for i in xrange(len(date))]

his = np.histogram(u, bins=50, range=(0,2))
for i in xrange(len(his[0])):
 	his[0][i] *= exp(his[1][i])

pl.clf()
pl.plot(his[1][1:], his[0])
pl.gca() #.set_xscale("log")
pl.show()


# for i in xrange(len(h[0])):
# 	h[0][i] *= exp(h[1][i]*2)
# print "after"
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
