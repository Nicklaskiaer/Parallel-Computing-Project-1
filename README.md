# Parallel Computing Project

Dependencies:

- OpenMP
- C++ compiler (g++14 or higher)
- Make

Guide: \\
Go to the cpp-implementation directory, and run the following command:

```bash
make
```

This will compile the code and create the executable. To run the code, use the following command:

```bash
./main
```

This will run the program, asking the user for a matrix size, and run the symetry check and transpose functions of all implementations. The results will be printed to the console.

To clean the directory, use the following command:

```bash
make clean
```

This will remove the executable and object files from the directory.

# Implementation

## General Information

The implementations return a struct symmetryResult, or transposeResult which contains the following fields:

```cpp
struct symetryResult {
    bool isSymetric;
    double duration;
};

```

```cpp

struct transposeResult {
    int **new_matrix;
    double duration;
};
```

The different implementations are split into different files, all using header files to include the necessary functions and structs.
The helpers file contains the structs, a function to print a matrix, functions that run a given function and times it. Returning the corresponding result struct.
The main file is used to run the program, and call the functions from the different implementations.

## Sequential Implementation

This implementation is sequential and uses a single thread to run the symetry check and transpose functions.
The symetry check function checks if a matrix is symmetrical, by comparing elements (i, j) with elements (j, i) one by one.
The transpose function transposes a matrix, by swapping elements (i, j) with elements (j, i) one by one.

## Implicit Parrallelization

This implementation relies on blocking/tilling and loop unrolling to parallelize the symetry check and transpose functions.
The improvements come from breaking the matrix into BLOCK_SIZE × BLOCK_SIZE tiles. And unrolling the inner block loops to process 4 elements at a time.

### Blocking/Tiling

Blocks ensure that smaller chunks of the matrix are accessed in contiguous memory, improving spatial locality and making better use of the CPU cache. By processing one block at a time, the likelihood of cache hits increases, reducing the time spent on memory access.

### Loop Unrolling

Loop unrolling reduces the overhead of loop control, by processing multiple elements in a single iteration. This reduces the number of iterations required to process the entire matrix, and the number of conditional jumps, improving performance.
This is achieved by checking 4 elements of the blocks at a time, and returning false if any of the 4 elements is not symmetrical.

In the end the unrolled loop also checks the remaining elements of the block, if the block is not a multiple of 4.

## Explicit Parrallelization

This implementation uses OpenMP to parallelize the symmetry check and transpose functions. By distributing the workload across multiple threads.

### OpenMP Parallelization

OpenMP's
#pragma omp parallel for collapse(2)
directive is used to parallelize the nested loops in both functions. This allows the two-dimensional iteration space to be split across multiple threads, ensuring efficient utilization of CPU cores. The collapse(2) clause merges the loops, providing finer-grained parallelism and improving load balancing.
