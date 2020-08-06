#!/usr/bin/python

import argparse
import numpy as np
import matplotlib.pyplot as plt

# Inputs
parser = argparse.ArgumentParser()
parser.add_argument('-shape', type=int, nargs=2, default=[512, 512],
        help='Number of particles in [x, y] directions')
parser.add_argument('-x', type=int, nargs=2, default=[-1, 1],
        help='Domain of x: [xmin, xmax]')
parser.add_argument('-y', type=int, nargs=2, default=[-1, 1],
        help='Domain of y: [ymin, ymax]')
parser.add_argument('-type', type=str, default='uniform',
        choices=['uniform', 'step', 'radial'],
        help='Type of initial heat distribution')
parser.add_argument('-r', type=float, default=1.0,
        help='Radius of radial heat distribution (ignored for other types)')

args = parser.parse_args()

# Create the coordinate grid of particles
x = np.linspace(args.x[0], args.x[1], num=args.shape[0],
        endpoint=True)
y = np.linspace(args.y[0], args.y[1], num=args.shape[1],
        endpoint=True)

xx, yy = np.meshgrid(x, y)
zz = np.zeros((args.shape[0], args.shape[1]))

# Particles are fixed on the grid, set forces and
# velocities to zero
vv = np.zeros((args.shape[0], args.shape[1]))
ff = np.zeros((args.shape[0], args.shape[1]))

# Set masses (used as mass density)
mm = np.ones((args.shape[0], args.shape[1]))

# Set initial temperature (1 everywhere,
# corresponding to equilibrium)
tt = np.ones((args.shape[0], args.shape[1]))

# Set "boundary" points (don't update their
# temperature during the simulation)
bb = np.zeros((args.shape[0], args.shape[1]))

# Uniform temperature distribution
if args.type == 'uniform':
    hv = np.zeros((args.shape[0], args.shape[1]))
    print(hv)

# Delta function temperature distribution
elif args.type == 'step':
    hv = np.zeros((args.shape[0], args.shape[1]))
    hv[:, int(0.25*args.shape[0])] = -1.0*args.shape[0]
    hv[:, int(0.75*args.shape[0])] = 1.0*args.shape[0]
    print(hv)

# Radial temperature distribution
else:
    hv = np.zeros((args.shape[0], args.shape [1]))
    hv[np.where((xx**2 + yy**2) < args.r)] = 1.0
    bb[0, :] = 1
    bb[-1, :] = 1
    bb[:, 0] = 1
    bb[:, -1] = 1
    print(hv)

# Stack the columns for output
out = np.column_stack((xx.flatten(order='C'),
        yy.flatten(order='C'),
        zz.flatten(order='C'),
        vv.flatten(order='C'),
        vv.flatten(order='C'),
        vv.flatten(order='C'),
        ff.flatten(order='C'),
        ff.flatten(order='C'),
        ff.flatten(order='C'),
        mm.flatten(order='C'),
        tt.flatten(order='C'),
        hv.flatten(order='C'),
        bb.flatten(order='C')))

np.savetxt('input.csv', out, header='X Y Z VX VY VZ FX FY FZ M T HV B',
        delimiter=' ', fmt='%.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %d')
