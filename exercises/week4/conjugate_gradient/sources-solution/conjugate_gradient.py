from __future__ import print_function
import numpy as np


def solve(A, b, x_old, max_iter=50, tol=1e-8):
    solutions = []
    solutions.append(x_old)

    r_old = b - np.einsum('ij,j->i', A, x_old)
    p_old = r_old

    iiter = 0
    convergence = False
    while iiter <= max_iter:
        Ap_old = np.einsum('ij,j->i', A, p_old)
        alpha = float(np.einsum('i,i->', r_old, r_old)) / float(
            np.einsum('i,i->', p_old, Ap_old))

        x_new = x_old + alpha * p_old
        r_new = r_old - alpha * Ap_old

        solutions.append(x_new)
        convergence = testConvergence(x_new, x_old, tol)

        if convergence:
            return x_new, solutions

        beta = np.einsum('i,i->', r_new, r_new) / np.einsum('i,i->', r_old,
                                                            r_old)
        p_old = r_new + beta * p_old
        r_old = r_new
        x_old = x_new

        iiter += 1

    return False


def testConvergence(x_new, x_old, tol):
    delta = x_new - x_old
    error = np.linalg.norm(delta)
    return error < tol
