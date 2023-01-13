# HOMEWORK 4

Authors: Benjamin Helfrecht and Edoardo Baldi

## Compilation and execution instructions

1. Create a build directory in the main project directory (.): `mkdir -p build`
2. Enter the build directory and issue `cmake ..`. The compilation will also copy the Python script `particles.py`, the main wrapper to the particles code. If you want to compile also the Google tests, pass the option `BUILD_GTESTS` to CMake.
3. `make` will then produce a particles executable, a library for the particles code,
   and a pybind library for the particles code that can be used with `particles.py`.
4. An input for a materials point simulation can be created with `particles.py build -shape 12 12 -type step`. (`particles.py build --help` will print detailed usage and options to build input file.)
5. Once the input is generated, running `particles.py run material_point` will execute a material points simulation. (Use `particles.py run --help` to print options available for a run.)

## Exercise 1

2. The `createSimulation` function is overloaded to take a functor as an argument.
   This allows the user to build and specify additional parameters for the compute object,
   such as the conductivity and heat capacity (for `ComputeTemperature`). In other words,
   it allows the user to customize the computation that governs the evolution of the system.
   If a user does not specify a custom function, the compute object is initialized
   with default values. In principle, this functionality could also be 
   extended to different compute types, for example, using it to specify the gravitational
   constant in a planets simulation or the contact penalty in a ping poing ball simulation
   while also adding an additional `ComputeBoundary` to the system.

## Exercise 2

2. Because the `addCompute` function of the `SystemEvolution` takes as argument a shared pointer
   of type Compute, this must be specified as an additional template parameter in the
   python bindings. In other words, we need to specify that `Compute` objects
   (`Compute`, `ComputeTemperature`, `CsvWriter`, etc.) are managed with a "special holder type".
   The [Smart pointers](https://pybind11.readthedocs.io/en/stable/advanced/smart_ptrs.html) section of the Pybind11 documentation gives additional details.
