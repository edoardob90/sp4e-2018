#!/usr/bin/env python3

import sys
import numpy as np
import matplotlib.pyplot as plt

# Print help if fewer than required arguments are passed
if len(sys.argv) < 2:
    print('Usage: python3 PlotSeries.py [file containing data to plot] [delimiter]')
    sys.exit(-1)

# Take filename as first positional argument
filename = sys.argv[1]

# Take delimiter as second (optional) positional argument
if len(sys.argv) > 2:
    delim = sys.argv[2]
    data = np.loadtxt(filename, delimiter=delim, unpack=True)

# If no second argument, delimiter defaults to whitespace
else:
    data = np.loadtxt(filename, unpack=True)

# Plot the series
fig = plt.figure()
axs = fig.add_subplot(1, 1, 1)
axs.plot(data[0], data[1], linestyle='-', marker='o', c='k')

# If that data contains a third column
# (e.g., the analytical prediction), plot that too
if len(data) > 2:
    axs.plot(data[0], data[2], linestyle='--', c='r')
plt.show()
