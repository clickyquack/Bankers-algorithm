# Banker's Algorithm
This is a C++ demonstration of the banker's algorithm as used for deadlock avoidance. In the example used, there are 5 processes and 3 resource types. The default state is a safe state with a safe sequence of `P3 -> P1 -> P0 -> P2 -> P4`.
## Data used by algorithm
- The "Available" vector (for which the implementation uses a vector of integers of size 3) holds the number of available instances of each resource type. In this case, length 3.
- The "Allocation" matrix (for which the implementation uses a size 5 vector of size 3 vectors of integers) holds the number of instances of each resource type currently being allocated to each process. In this case, the matrix size is 5x3
- The "Max" matrix (for which the same data structure as the "Allocation" matrix is used) holds the maximum number of instances of each resource type that may be requested by each process. In this case, the matrix size is also 5x3.

The input file input.txt is structured such that the table for each of these is listed in the order given, separated by an empty line. Each column is separated by a space and correpsonds to resource type A, B, or C in order. Each row is separated by a new line and corresponds to the process, P0 through P4 in order. Note that the "Available" table is one row long because the processes are not relevant to it. input.txt currently stores an example state of the system's processes and resources to be used to demonstrate operation of the algorithm. In banker.cpp, the readInput function is used to read the input file and properly store its data in the relevant data structures.

- The "Need" matrix (for which the same data structure as the "Allocation" matrix is used) holds the number of instances of each resource type that may be needed by each process. Its matrix size in this case is also 5x3. It is not given in input.txt, because any element of the Need matrix can be found as the difference of the corresponding elements stored in the Max and Allocation matrices. Or, for the ith process and jth resource type, Need[i, j] = Max[i, j] - Allocation[i, j]. In banker.cpp, this is done in the main function.
## Operation of algorithm
In banker.cpp, the bankersAlgorithm function checks whether the system is in a safe state. If so, it returns true and stores the safe sequence of process execution that could be used to avoid deadlock (stored a vector of integers of the process numbers in order of the safe sequence). Otherwise, it returns false.

It operates by first initializing a "Work" vector to the available vector's state, to be used to store the number of instances of each resource that would be available at the current point in the safe sequence as it is being found. It also initializes a "Finish" vector to all false values, to be used to store whether each process would have finished yet at the current point in the safe sequence as it is being found. 

The algorithm then tries to place each process in a safe sequence to execute them to avoid deadlock. The algorithm tries to find a process not yet marked as finished in Finish for which its resource needs in Need do not exceed the current limits stored in Work. If it finds one, the process is marked as finished and its allocated resources are added to Work for the next processes to potentially use, and it is placed in the safe sequence. It repeats this process until either all processes are marked finished (in which case the function returns true), or until it is unable to find another unfinished process with less resource needs than what would be available to it (in which case the function returns false).
## Result
If the state given in input.txt is safe, the program will print:
```
The system is in a safe state.
Safe sequence:
```
followed by the safe sequence it found. For the default example state given, it would print:
```
Safe sequence: P3 -> P1 -> P0 -> P2 -> P4
```
If the state is not safe, the program will print:
```
The system is not in a safe state.
```
