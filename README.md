# Integer Collection & Intervals  

 An interesting project task on data structures & algorithms, object-oriented programming, unit testing and documentation writing.

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
The respective `README.md` files contain more details on specific build instructions, implementations and reasonings.

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

All unit tests passed successfully with reasonable time: (Integer Collection: ~1s; Intervals: ~8s). See `tests.cxx` for unit tests.