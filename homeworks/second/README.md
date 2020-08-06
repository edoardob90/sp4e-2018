# Homework n. 2

Authors: Benjamin Helfrecht, Edoardo Baldi

## Compilation
1. Create a `build` directory within the main folder: `mkdir -p ./second/build`
2. Enter and issue cmake/make: `cd build; cmake .. && make`

## Usage
1. Run `./main -h` to show an help on the available options
2. For example: to compute the Arithmetic series up to 1000 and printing every 10 steps, run

```
./main -t ari -n 1000 -f 10
```

To plot the results, use the `PlotSeries.py` script in the `src` folder. The script requires the name of the file containing the data to plot along with the delimiter (if the delimiter is whitespace, only supply the filename). Call as:

```
python3 PlotSeries.py [filename] [delimiter]
```

For example:

```
python3 PlotSeries.py out.csv ','
```

## Comments

### Exercise 2.1

We believe that the best strategy to divide the work is for one person to work on building the Series class family while the other builds the Dumper class family.


### Exercise 3.7

We note that if the user wishes to set the separator as an escaped character (e.g., a newline `\n` or tab `\t`), the delimiter will instead be the literal string "\n" or "\t". This is because the string containing the separator is interpreted at runtime, and therefore the compiler, which normally converts instances of `\n`, `\t`, etc. to the appropriate character (i.e., a newline or tab) is not involved in interpreting the input string from the command line.

Consequently, we would think it would be better to assign the separator based on the file extension.

### Exercise 3.10

We decided to write our simple yet flexible input parser. The source file is `InputParser.hh`.

Features of this parser:

1. can check if an option is present;

2. can parse an option for an argument that can be: (1) integer or (2) a string. The conversion to integer is done via the STL function `std::stoi`, which raises an exception if the conversion isn't possible;

3. supports optional and compulsory arguments (but **not yet** default values, except those already managed by class's constructors).

The problem discussed above about the "escaped" field separator is dealt as follows: first, the parser checks if a literal `\t` or `\n` is passed as argument to `-s` option; if this is the case, the return value of `getOptionArgument` is set to be correctly translated at compilation time.


### Exercise 5

1. The complexity of the program is of order $N^2$, where $N$ is the number of terms in the sum. Consider $N = 3$. Then the number of required operations is $N + (N-1) + (N-2)$, which is of order $N^2$.

4. Saving the `current_term` and `current_index` variables reduces the complexity to order $N$, since the sum doesn't need to be re-computed at each call of the `compute` function.

5. At best, the complexity would still be of order $N$ because $N$ addition operations must to carried out to compute the sum. Summing the terms reversely is simply a matter of reversing the order of the for loop in which the sum is computed,
as the number of terms in the sum is already known and supplied by the user.
