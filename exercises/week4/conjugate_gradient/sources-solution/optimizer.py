from __future__ import print_function
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import conjugate_gradient as cg
from scipy.optimize import minimize

sol_steps = []


def plot(func, sol_steps, title):

    x = np.linspace(-3, 3, 100)
    y = np.linspace(-3, 3, 100)
    x, y = np.meshgrid(x, y)
    z = func([x, y])

    xy = np.stack(sol_steps, axis=0)
    zs = func([xy[:, 0], xy[:, 1]])

    fig = plt.figure()
    ax = Axes3D(fig)
    ax.plot_surface(x, y, z, linewidth=0, antialiased=True,
                    cmap=plt.cm.viridis, alpha=0.2)
    ax.contour(x, y, z, 10, colors="k", linestyles="solid")
    ax.plot(xy[:, 0], xy[:, 1], zs, 'ro--')
    ax.grid(False)
    ax.set_title(title)

    plt.xlabel('$x$')
    plt.ylabel('$y$')
    plt.show()


def cgSolve(fun, A, b, x0, max_iter, tol):
    res = cg.solve(A, b, x0, max_iter=max_iter,
                   tol=tol, callback=getIterationSteps)
    plot(fun, sol_steps, 'Conjugate Gradient')
    return res


def scipySolve(fun, x0, max_iter, tol):
    sol_steps.append(x0)
    res = minimize(fun, x0, method='BFGS', callback=getIterationSteps,
                   tol=tol)
    plot(fun, sol_steps, 'BFGS')
    return res.x


def getIterationSteps(Xi):
    sol_steps.append(Xi)
