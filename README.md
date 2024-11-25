# intro-parco-h1

guide:

compilation cpp:

/opt/homebrew/bin/g++-14 -o src/executables/sequential_implementation src/sequential_implementation.cpp
/opt/homebrew/bin/g++-14 -o src/executables/implicit_parallelization src/implicit_parallelization.cpp

with openmp:
/opt/homebrew/bin/g++-14 -fopenmp -o src/executables/explicit_parallelization src/explicit_parallelization.cpp

## Data and Results

### Sequential Implementation

Symmetry check time: 0.493905 seconds\
Transpose time: 0.539214 seconds\
Matrix is symmetric

### Implicit Parallelization

With O2\
Symmetry check time: 0.206490 seconds\
Transpose time: 0.619467 seconds\
Matrix is symmetric

With O3\
Symmetry check time: 0.194329 seconds\
Transpose time: 0.619037 seconds\
Matrix is symmetric

### Explicit Parallelization

Without optimization\
Symmetry check time: 0.776487 seconds\
Transpose time: 2.123414 seconds\
Matrix is symmetric

With O2\
Symmetry check time: 0.608189 seconds\
Transpose time: 2.547630 seconds\
Matrix is symmetric

With O3\
Symmetry check time: 0.618733 seconds\
Transpose time: 2.413074 seconds\
Matrix is symmetric
