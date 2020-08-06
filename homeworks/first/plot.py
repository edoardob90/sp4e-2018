#!/usr/bin/env python3

"""
    Plotting function for optimizer.py and conjugate_gradient.py
"""

# Numpy
import numpy as np

# Plotting
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm

def plot3d(xs, ys, zs, func, grid_range=[-3.,3.]):
    """
        xs: x-coordinate of solution (1-D array)
        ys: y-coordinate of solution (1-D array)
        zs: f(xs, ys)
    """
    # Setup plot
    X = np.arange(grid_range[0], grid_range[1], 0.25)
    Y = np.arange(grid_range[0], grid_range[1], 0.25)
    X, Y = np.meshgrid(X, Y)
    Z = func([X,Y])
    fig=plt.figure()
    ax = fig.add_subplot(1,1,1, projection='3d')
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')
    ax.plot_surface(X, Y, Z, cmap=cm.coolwarm, linewidth=0, antialiased=False, alpha=0.75)
    ax.contour(X, Y, Z, colors='black')
    xy_path = np.stack((xs, ys), axis=1)
    # Plot minimization steps
    ax.plot(xy_path[:,0], xy_path[:,1], zs, marker='o', linestyle='--', color='red', linewidth=1.0)
    ax.view_init(elev=50.0, azim=140.0)
    # Show
    plt.show()

