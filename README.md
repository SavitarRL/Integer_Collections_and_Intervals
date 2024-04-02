# Integer Collection & Intervals  

 An interesting project task on data structures & algorithms, object-oriented programming, unit testing and documentation writing.

## Problem overview
#### Integer collection
Add appropriate data members to the IntegerCollection class and implement the missing methods in the included code that stores a collection of integers. On construction, the collection should be empty. The same number may be stored more than once.

Implement the following methods:

1. Insert(int x). Insert an entry for the value “x”.
2. Erase(int x). Remove one entry with the value “x” (if one exists) from the collection.
3. Erase(int from, int to). Remove all the entries with a value in the range [from, to).
4. Count(int from, int to). Count how many entries have a value in the range [from, to).

#### Intervals
Implement a function that takes as input 

•	A closed integer interval $I$, 
•	a collection of intervals $A_1... A_n$ 

and checks if $I \subseteq ⋃_j 𝐴_𝑗$. (i.e. if every element of $I$ is in the union of the $A_i$)

## Overall File Structure

```
├── IntegerCollection
│   ├── Makefile
│   ├── README.md
│   ├── collection.cxx
│   ├── main_collection.cxx
│   ├── test.h
│   └── tests.cxx
├── Intervals
│   ├── Makefile
│   ├── README.md
│   ├── intervals.cxx
│   ├── main_intervals.cxx
│   ├── test.h
│   └── tests.cxx
└── README.md               # this README file
```
The respective `README.md` files contain more details on the tasks, specific build instructions, implementations, and explanations.

## Requirements
- **C++ Compiler**: The project requires a C++ compiler. The Makefile is configured to use `g++` as the default compiler.

- **C++ Standard**: The project code is written in C++14.

- **Make**: The project is built using a Makefile and the ``make`` command. Please install according to your operating system. For Linux OS, install by running the following in the terminal:
```
sudo apt install make
```

## Tested Environment

Application tested and run in: `Ubuntu 22.04.1 LTS`

## Build Instructions

To run all tests for **Integer collection**
```
./IntegerCollection/main_collection
```

To run all tests for **Intervals**
```
./Intervals/main_intervals
```

All unit tests passed successfully within a reasonable time: (Integer Collection: ~1s; Intervals: ~8s). See `tests.cxx` for unit tests in respective directories.
