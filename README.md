# Banker's Algorithm
This is a C++ demonstration of the banker's algorithm as used for deadlock avoidance. In the example case used, there are 5 processes and 3 resource types.
## Data used by algorithm
- The "Available" vector (for which the implementation uses a vector of integers of size 3) holds the number of available instances of each resource type. In this case, length 3.
- The "Allocation" matrix (for which the implementation uses a size 5 vector of size 3 vectors of integers) holds the number of instances of each resource type currently being allocated to each process. In this case, the matrix size is 5x3
- The "Max" matrix (for which the same data structure as the "Allocation" matrix is used) holds the maximum number of instances of each resource type that may be requested by each process. In this case, the matrix size is also 5x3.

The input.txt file is structured such that the table for each of these is listed in the order given, separated by an empty line. Each column is separated by a space and correpsonds to resource type A, B, or C in order. Each row is separated by a new line and corresponds to the process, P0 through P4 in order. Note that the "Available" table is one row long because the processes are not relevant. It currently stores an example state of the system's processes and resources to be used to demonstrate operation of the algorithm.

- The "Need" matrix (for which the same data structure as the "Allocation" matrix is used) holds the number of instances of each resource type that may be needed by each process. Its matrix size in this case is also 5x3. It is not given in input.txt, because any element of the Need matrix can be found as the difference of the corresponding elements stored in the Max and Allocation matrices. Or, for the ith process and jth resource type, Need[i, j] = Max[i, j] - Allocation[i, j].
## Operation of algorithm
