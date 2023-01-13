#!/usr/bin/env python3

import numpy as np
import os, sys
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from plot import plot3d

def S(x):
    """
        Linear algebra formulation of the 
        function to minimize

        x: vector of first guess at coordinates
    """
    A = np.array([[4.0, 1.0], [1.0, 3.0]])
    b = np.array([1.0, 2.0])
    Ax = np.einsum('ij,i', A, x)
    xb = np.einsum('i,i', x, b)
    return 0.5*np.einsum('i,i', x, Ax) - xb

def S2(X):
    """
        Function definition for minimization

        X: list of x, y coordinates
    """
    x, y = X
    return 2*x**2 + 1.5*y**2 + x*y - x - 2*y + 6

def cg(A, b, x, tol=1.0E-10, max_steps=500):
    """
        Conjugate gradient routine

        A: Coeffient matrix
        b: Coefficient vector
        x: initial guess at solution
        tol: tolerance for minimization
        max_steps: maximum number of CG steps
    """
    r = b - np.einsum('ij,j', A, x)
    rr0 = np.einsum('i,i', r, r)
    p = r
    xs = [x.copy()] 
    z = [S(x)]

    for i in range(1, max_steps+1):
        Ap = np.einsum('ij,j', A, p)
        alpha = rr0/np.einsum('i,i', p, Ap)
        x += alpha*p
        xs.append(x.copy())
        z.append(S(x))
        r -= alpha*Ap
        rr1 = np.einsum('i,i', r, r)
        if np.sqrt(rr1) < tol:
            print('Found minimum, |r| = ', np.sqrt(rr1))
            print('Minimum found in ', i, ' steps')
            print('Minimum = ', x)
            break
        p = r + (rr1/rr0)*p
        rr0 = rr1
        if i >= (max_steps+1):
            print('Reached maximum number of steps; exiting minimization')
            print('|r| = ', np.sqrt(rr1))
            print('x = ', x)

    return np.stack(xs, axis=0), np.asarray(z)

# Build function to minimize
A = np.array([[4.0, 1.0], [1.0, 3.0]])
b = np.array([1.0, 2.0])
x0 = np.array([-3.0, -3.0])

# Minimize the function
xs, z = cg(A, b, x0)

# Plot solution and minimization steps
plot3d(xs[:, 0], xs[:, 1], z+6, S2, grid_range=[-3.0, 3.0])
