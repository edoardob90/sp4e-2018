#!/usr/bin/env python3

import optimizer as opt
import numpy as np
import argparse


def func(x):
    return 2*x[0]**2 + 1*x[0]*x[1] + 1.5*x[1]**2 - x[0] - 2*x[1] + 6


A = np.array([[4, 1], [1, 3]])
b = np.array([1, 2])


def optimize(method='cg'):
    max_iter = 50
    tol = 1e-6
    x0 = np.array([2, 1])

    # --- exo1 -------
    if method == 'python':
        res = opt.scipySolve(func, x0,  max_iter, tol)
        print('Scipy Solution : ', res)

    # --- exo2 -------
    elif method == 'cg':
        res = opt.cgSolve(func, A, b, x0, max_iter, tol)
        print('Conjugate Gradient Solution : ', res)

    else:
        raise RuntimeError('unknown method: ' + str(method))


if __name__ == '__main__':

    parser = argparse.ArgumentParser(
        description='Optimization exercise in python')

    parser.add_argument(
        '-m', '--method', type=str,
        help=('Specify the method to use for the optimization.'
              ' Can be cg/python'), default='cg')

    args = parser.parse_args()
    optimize(args.method)
