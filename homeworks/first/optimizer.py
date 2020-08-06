#!/usr/bin/env python3

"""

Exercise 1
Author: Edoardo Baldi

"""

# Our plotting package
import plot
from scipy.optimize import minimize

# Function to minimize
def f_to_minimize(coords):
    x,y=coords
    return 2*x**2 + (3/2)*y**2 + x*y - x - 2*y + 6

# Function to pass as callback
def getIterationSteps(solution):
    global step
    step += 1
    x,y = solution
    z = f_to_minimize(solution)
    print("At step {:d}: x = {:f}, y = {:f}, f(x,y) = {:f}".format(step,x,y,z))
    x_step.append(x)
    y_step.append(y)
    z_step.append(z)


# Minimize
step=0
x_step = []
y_step = []
z_step = []
OptRes = minimize(f_to_minimize, 
                  (-3.,-3.), 
                  method='CG', 
                  tol=1.e-10,
                  callback=getIterationSteps)
# Plot
plot.plot3d(x_step, y_step, z_step, f_to_minimize)
