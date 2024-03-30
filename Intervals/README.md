# Intervals

Problem Description
------------------
Implement a function that takes as input 

•	A closed integer interval $I$, 

•	a collection of intervals $A_1... A_n$ 

and checks if $I \subseteq ⋃_j 𝐴_𝑗$. (i.e. if every element of $I$ is in the union of the $A_i$)

## File Structure
```
├── Makefile                   # compiling this project
├── README.md                  # this README file
├── intervals.cxx              # implementation of the Interval class and the required IsIntervalInUnionOfOthers function 
├── main_intervals             # executable of the program (runs all tests for this question)
├── main_intervals.cxx         # file containing main() to run all unit tests
├── test.h                     # header file for test framework
└── tests.cxx                  # unit tests for intervals.cxx
```
Note that additional unit tests have been added to check the implementation of the ` GetUnionisedIntervals` function in `intervals.cxx`.

## Build Instructions

In the terminal, go to the current directory.

- To build and run all tests:
    ```
    make
    ```
- To run all tests (if `main_intervals` executable is present):
    ```
    ./main_intervals
    ```

Reasoning and Implementation
----------------
#### A brute-force, incremental solution

One possible solution is to loop through every interval $A_j$. First, we expand $A_j$ using a for loop and store the range using a `std::vector<int>`. We can then loop through this vector. For each iteration, we compare the interval range with this vector of integers and remove elements which are within the interval using `std::vector::erase()`. We return true whenever the vector is empty. If the for loop ends and there are still elements within the vector, there are some elements which are not covered, hence the function returns false.

The solution above works well with a small number of elements, but will not optimally perform when $L$ is large. This is because, within the for loop, we are using the `std::vector::erase()` function. This function has to find the element in the vector first and then delete it. This is comparable to a nested for-loop operation, which indicates a time complexity of $\mathcal{O}(L^2)$.

#### The Sorted, Unionised Solution

My solution is quite different from the above brute-force solution but achieves an improved overall time complexity of $\mathcal{O}(n\log(n))$, where $n$ is the length of $A$. The implementation also accounts for disjoints between interval collections. My solution involves the following steps:

1. Immediate comparison when $n$ is less than or equal to zero
- Returns false when the interval or collection is empty
- Compares directly when there is a single continuous interval, returns true if all elements of $I$ to be in $A_1$ by comparing lower and upper bounds of both $I$ and $A_1$
- both have time complexities of $\mathcal{O}(1)$. 

2. Implement Union of $A$ if $n$ is larger than 1
- sort the intervals based on the start value using `std::sort`with time complexity of $O(n\log(n))$
- create a `std::vector<Interval>` to store the unionised $A$
- using a two-pointer method, loop through sorted intervals, and merge the overlapping intervals using a stack, implemented by `std::stack`
    - merge the current interval with the next interval if the end range of the current interval and the start range of the next interval can be connected
    - if cannot connect, this indicates a disjointed interval, which is added to the vector, as well as the merged interval
    - loop until the right pointer reaches the end
- this has a time complexity of $\mathcal{O}(n)$

3. Compare directly again when the length of the union of $A$ is 1
- if there is a completely merged union of $A$, we do the same thing as in 1. This operation has a time complexity of $\mathcal{O}(1)$.

4. Binary search for disjointed intervals
- If the length of the union of $A$ is larger than 1, we use a custom binary search to check if the input interval is in the unionised vector of intervals
- We are allowed to do binary search as step 2. ensures a sorted, unionised set of intervals, making the time complexity $\mathcal{O}(\log{n})$.

Overall when $n$ is large, step 2 using `std::sort` with time complexity of $O(n\log(n))$ dominates, and hence the overall implementation has the time complexity of $O(n\log(n))$, which is a huge improvement comparing to the quadratic scaling of the brute force approach.

#### Side note relating to `integer collection`: 
Within the nested for loop, we are using `std::vector::erase()`, similar how it will be used in my implementation in `integer collection`. It is possible we can expand $A_j$ using a for loop and store the range using `std::map<int, size_t>`, as from the `integer collection` class. This will improve the overall time complexity to $\mathcal{O}(N\log N)$, where $N$ is the length of the `std::map`, which will be dependent on the elements within unionised $A$.
