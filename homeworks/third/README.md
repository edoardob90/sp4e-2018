# HOMEWORK 3

*Authors: Benjamin Helfrecht and Edoardo Baldi*

## Exercise 1

The `MaterialPoint` is a derived class from the `Particle` which adds the properties related to heat transfer. `MaterialPointsFactory` is a derived factory which sets up a simulation of a system of material points.

`Matrix` is a template class that allows easy manipulation of 2D data.

`FFT` is class to easily compute the 2D Discrete Fourier Trasform and frequencies of matrix of data.

## Exercise 2

With the FFTW library installed, compile the code as follows:

1. In the root directory of the project, create a build directory: `mkdir -p build`
2. Enter the build directory and issue `cmake ..`
__NOTE__: if the FFTW library isn't installed in a standard path, use the CMake variable `FFTW_USER_PATH=/path/to/fftw/root`.
3. `make` will produce an executable named `particles` in a `bin` subdirectory. The main library is placed in the `lib` subdirectory.


## Exercise 3

In the `bin` directory, run the `test_fft` executable to perform the GTests on the implemented FFT routines (forward, backward, and frequencies computation).
The FFT frequencies are compared against the expected output from numpy.fft.fftfreq.

## Exercise 4

The tests for the homogeneous, delta function, and radial heat distributions can be run with the `test_heat` executable in the `bin` directory

### Simulation with a point-like heat distribution

1. Run the script (in the `src` folder) `generate_input.py -shape 64 64 -type step` to produce an input file of 4096 particles.

2. `mkdir -p ./dumps`

3. Launch the `particles` code: `particles 1000 100 input.csv material_point 1.0`. This would run the simulation for a thousand of steps with 1.0 as timestep, dumping every 100 steps.

4. As a quick visualization of the final temperature distribution, run the script `read_output.py dumps/step-00900.csv`.


### Simulation with a radial heat distribution

To produce a radial heat distribution with radius R, run the script `generate_input.py -shape 64 64 -type radial -r R`. Launch the `particles` code as above.

To setup the boundary conditions, we decided to have an additional field in the input with a true/false flag for whether or not to update the temperature at that point. The `computeTemperature` updates the temperature of those points which have the flag set to false.

We chose to implement it in this way for two reasons:

1. having the information of the boundary points in the input saves an extra NxN loop to identify the boundary points within the code.

2. the boundary shape can be customized directly in the input file, instead of changing the code for different types of boundary conditions.

We thought about writing a class for "Setup methods" that would be executed once at the beginning of the simulation (before the `evolve`). This would allow the user to further customize the initial conditions of the simulation and avoid the reinitialization of constant quantities. We don't think the extra effort of implementing this would be worth it just for the material point simulation. Maybe with the addition of simulation types and extra features it would be worthwhile (for example, if we wanted to fix the position of a planet).
