#!/usr/bin/python
import numpy as np
import pylab as pl
from math import log
date = [line.strip().split() for line in open("ito.out")]
x = [float(date[i][0]) for i in xrange(len(date))]
# y = [float(date[i][1]) for i in xrange(len(date))]
# print y
# print np.logspace(min(y), max(y), 40)
h = pl.hist(x) #, bins=np.logspace(min(y), max(y), 40)
print "h=", h
pl.gca() #.set_xscale("log")
pl.show()