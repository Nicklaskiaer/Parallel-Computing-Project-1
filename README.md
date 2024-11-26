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

# Results

<details>
<summary>Running for n = 2^4</summary>

Time taken by checkSymSeq: 5e-06 seconds \
Time taken by checkSymImp: 4e-06 seconds \
Time taken by checkSymOMP: 5e-06 seconds \
Time taken by matTransposeSeq: 4e-06 seconds \
Time taken by matTransposeImp: 4e-06 seconds \
Time taken by matTransposeOMP: 6e-06 seconds

</details>

<details>
<summary>Running for n = 2^5</summary>

Time taken by checkSymSeq: 8e-06 seconds \
Time taken by checkSymImp: 7e-06 seconds \
Time taken by checkSymOMP: 1.7e-05 seconds \
Time taken by matTransposeSeq: 1.4e-05 seconds \
Time taken by matTransposeImp: 9e-06 seconds \
Time taken by matTransposeOMP: 1.9e-05 seconds

</details>

<details>
<summary>Running for n = 2^6</summary>

Time taken by checkSymSeq: 2.5e-05 seconds \
Time taken by checkSymImp: 2.3e-05 seconds \
Time taken by checkSymOMP: 6.3e-05 seconds \
Time taken by matTransposeSeq: 3.2e-05 seconds \
Time taken by matTransposeImp: 2.7e-05 seconds \
Time taken by matTransposeOMP: 6.8e-05 seconds

</details>

<details>
<summary>Running for n = 2^7</summary>

Time taken by checkSymSeq: 0.000106 seconds \
Time taken by checkSymImp: 7.2e-05 seconds \
Time taken by checkSymOMP: 0.000193 seconds \
Time taken by matTransposeSeq: 0.000133 seconds \
Time taken by matTransposeImp: 9.5e-05 seconds \
Time taken by matTransposeOMP: 0.000243 seconds

</details>

<details>
<summary>Running for n = 2^8</summary>

Time taken by checkSymSeq: 0.000453 seconds \
Time taken by checkSymImp: 0.000214 seconds \
Time taken by checkSymOMP: 0.000548 seconds \
Time taken by matTransposeSeq: 0.000552 seconds \
Time taken by matTransposeImp: 0.00015 seconds \
Time taken by matTransposeOMP: 0.000428 seconds

</details>

<details>
<summary>Running for n = 2^9</summary>

Time taken by checkSymSeq: 0.000809 seconds \
Time taken by checkSymImp: 0.000369 seconds \
Time taken by checkSymOMP: 0.00092 seconds \
Time taken by matTransposeSeq: 0.000869 seconds \
Time taken by matTransposeImp: 0.000677 seconds \
Time taken by matTransposeOMP: 0.001928 seconds

</details>

<details>
<summary>Running for n = 2^10</summary>

Time taken by checkSymSeq: 0.003163 seconds \
Time taken by checkSymImp: 0.001686 seconds \
Time taken by checkSymOMP: 0.00389 seconds \
Time taken by matTransposeSeq: 0.003824 seconds \
Time taken by matTransposeImp: 0.004011 seconds \
Time taken by matTransposeOMP: 0.008848 seconds

</details>

<details>
<summary>Running for n = 2^11</summary>

Time taken by checkSymSeq: 0.017173 seconds \
Time taken by checkSymImp: 0.005728 seconds \
Time taken by checkSymOMP: 0.011982 seconds \
Time taken by matTransposeSeq: 0.014781 seconds \
Time taken by matTransposeImp: 0.008988 seconds \
Time taken by matTransposeOMP: 0.021249 seconds

</details>

<details>
<summary>Running for n = 2^12</summary>

Time taken by checkSymSeq: 0.134523 seconds \
Time taken by checkSymImp: 0.018659 seconds \
Time taken by checkSymOMP: 0.040539 seconds \
Time taken by matTransposeSeq: 0.141086 seconds \
Time taken by matTransposeImp: 0.03673 seconds \
Time taken by matTransposeOMP: 0.087226 seconds

</details>
