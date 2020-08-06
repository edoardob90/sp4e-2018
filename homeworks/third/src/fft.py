#!/usr/bin/python

import numpy as np
import sys
import matplotlib.pyplot as plt

# Code used for debugging; iteratively solves
# the heat problem like the particles code,
# so that the results can be compared.

fname = sys.argv[1]

data = np.loadtxt(fname)

N = np.int(np.sqrt(len(data)))
pos = data[:, 0:3]
mass = data[:, 9]
t = data[:, 10]
hv = data[:, 11]

t = t.reshape((N, N))
hv = hv.reshape((N, N))
mass = mass.reshape((N, N))

x = pos[:, 0].reshape((N, N))
y = pos[:, 1].reshape((N, N))
z = pos[:, 2].reshape((N, N))

Lx = x[0, -1] - x[0, 0]
Ly = y[-1, 0] - y[0, 0]

freq = np.fft.fftfreq(N, d=1.0)
freq2D = np.einsum('i,j->ij', np.ones(N), freq)
freq2D = (freq2D**2 + freq2D.T**2)

dt = 1.
C = 1.0
k = 1.0

for i in range(0, 10000):
    t_fft = np.fft.fft2(t)
    hv_fft = np.fft.fft2(hv)
    dt_fft = 1.0/(mass*C)*(hv_fft-k*t_fft*freq2D)
    dt_ifft = np.fft.ifft2(dt_fft)
    t += dt*dt_ifft.real
    #print t

#t /= 4.0*np.pi**2*N**2/(Lx*Ly)
#print 'T: ', t
#plt.plot(x[0, :], t[0, :])
plt.imshow(t)
plt.show()
