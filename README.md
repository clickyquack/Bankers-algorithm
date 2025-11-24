# ABOUT
This is a C++ demonstration of the banker's algorithm as used for deadlock avoidance. A detailed description of how the program works is given in [Description.md](Description.md).

# HOW TO USE
In a Linux environment with g++ installed, in a terminal in a directory containing the banker.cpp and input.txt files, the program may be compiled by running the following command:
```
g++ -o banker banker.cpp
```
And then executed by running:
```
./banker
```
The input.txt file is structured such that the data for the "Available" table, then the "Allocation" table, then the "Max" table is written, each separated by an empty line. Each column is separated by a space and correpsonds to resource type A, B, or C in order. Each row is separated by a new line and corresponds to the process, P0 through P4 in order. Note that the "Available" table is one row long because the processes are not relevant to it. The values in the tables may be edited to any integer. By default, the number of processes is 5, and the number of resource types is 3, but this can be adjusted by changing the values that the NUM_PROCESSES and NUM_RESOURCES global constant integers are initialized to at the beginning of banker.cpp.
