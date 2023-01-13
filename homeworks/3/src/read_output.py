#!/usr/bin/python

import sys
import numpy as np
import matplotlib.pyplot as plt

fname = sys.argv[1]

data = np.loadtxt(fname)

N = np.int(np.sqrt(len(data)))
pos = data[:, 0:3]
mass = data[:, 9]
t = data[:, 10]
hv = data[:, 11]

t = t.reshape((N, N))
hv = hv.reshape((N, N))

x = pos[:, 0].reshape((N, N))
y = pos[:, 1].reshape((N, N))
z = pos[:, 2].reshape((N, N))

#plt.plot(x[0, :], t[0, :])
plt.imshow(t)
plt.show()
