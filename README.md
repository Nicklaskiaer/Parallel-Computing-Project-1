# intro-parco-h1

guide:

compilation:

/opt/homebrew/bin/g++-14 -o src/executables/sequential_implementation src/sequential_implementation.cpp
/opt/homebrew/bin/g++-14 -o src/executables/implicit_parallelization src/implicit_parallelization.cpp

with openmp:
/opt/homebrew/bin/g++-14 -fopenmp -o src/executables/explicit_parallelization src/explicit_parallelization.cpp

## Data and Results

### Sequential Implementation

With a randomly generated non symetric matrix of size 50000:

| Run | checkSym (seconds) | transpose (seconds) |
| --- | ------------------ | ------------------- |
| 1   | 0.003613           | 5.03482             |
| 2   | 1.8e-05            | 5.56534             |
| 3   | 1.1e-05            | 5.28677             |
| 4   | 0.002899           | 5.27521             |
| 5   | 1e-06              | 4.99414             |
| AVG | 0.0013084 s        | 5.231256 s          |

### Implicit Parallelization
