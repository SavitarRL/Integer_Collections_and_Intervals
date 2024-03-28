# Integer collection 
Add appropriate data members to the IntegerCollection class and implement the missing methods in the included code that stores a collection of integers. On construction, the collection should be empty. The same number may be stored more than once.

Implement the following methods:
1.	Insert(int x).  Insert an entry for the value “x”.
2.	Erase(int x).  Remove one entry with the value “x” (if one exists) from the collection. 
3.	Erase(int from, int to).  Remove all the entries with a value in the range [from, to).
4.	Count(int from, int to).  Count how many entries have a value in the range [from, to).

## File Structure
```
├── Makefile                # file to compile this project
├── README.md               # this README file 
├── collection.cxx          # implementation of the IntegerCollection class
├── main_collection         # executable of the program (runs all tests)
├── main_collection.cxx     # file containing main() to run all unit tests
├── test.h                  # header file for test framework
└── tests.cxx               # unit tests for collection.cxx
```

## Build Instructions

In the terminal, go to the current directory.

- To build and run all tests:
    ```
    make
    ```
- To run all tests (if `main_collection` executable is present):
    ```
    ./main_collection
    ```



Reasoning and Implementation
----------------
#### The Straightforward Solution
One possible solution is to store the collection of integers using `std::vector<int>` or `std::array<int>`, but as we are inserting and erasing elements in the collection, we have to always resize it. Hence, using `std::vector<int>` will be better. The overall space complexity will be $\mathcal{O}(n)$ where $n$ is the number of integers in the collection. Its operations will have the following implementation and time complexities:

1.	Insert(int x): using `std::vector::push_back()` adding the element into the list:  $\mathcal{O}(1)$
2.	Erase(int x): using `std::vector::erase()`, which finds the element required to be deleted first and then deletes it: $\mathcal{O}(n)$
3.	Erase(int from, int to): Same as the above, but would need $m = (to - from - 1) $  number of operations: $\mathcal{O}(mn)$
4.	Count(int from, int to): adding 1 whenever the element in the collection is within the range: $\mathcal{O}(n)$

The solution above works well with a small number of elements, but fails to optimally perform when $n$ is large. While inserting is constant with time, erasing and counting is linear with time. Moreover, erasing will perform less optimally as it is almost quadratic with time when $ m \approx n$. 

#### The Better Solution

My solution is to store the collection of integers with the data structure of a sorted hash map, implemented using ``std::map<int, size_t>``. Its key is the stored integer and its value is the number of occurrences of that integer. The overall space complexity will still be $\mathcal{O}(n)$, but its operations will have better time complexities using the following implementation:

1.	Insert(int x): 
    - using `std::map::insert()` to insert a new element of map if the constructor is empty or x is not in the map
    - or add the count of x by 1 if x is in the map. 
    - finding if x is in the map by using `std::map::find()`
    - time complexity: $\mathcal{O}(\log n)$

2.	Erase(int x): 
    - finding if x is in the map by using `std::map::find()`
    - if x is in the map, decrease its count by 1
    - remove item when count of x is 0
    - do nothing if x is not in map
    - time complexity: $\mathcal{O}(\log n)$
    
3.	Erase(int from, int to):
    - getting the lower and upper bound iterators using `std::map::lower_bound()`
    - using `std::map::erase()` to erase each element within the bounds if elements exist
    - time complexity: $\mathcal{O}(m\log n)$
4.	Count(int from, int to): 
    - getting the lower and upper bound iterators using `std::map::lower_bound()`
    - adding 1 whenever the element in the collection is within the bounds 
    - time complexity: $\mathcal{O}(m\log n)$

For this implementation, the space complexities are equal. Although it is less optimal to use insert (constant vs logarithmic), but for other operations, a logarithmic scaling is way better than linear scaling with $n$ when $n$ is large. 

The logarithmic scaling is because ``std::map`` is implemented as a self-balancing Binary Search Tree (BST), or a Red–black tree. Its root is the middle element, and values less than the root's value are on the left and values larger than the root's value are on the right. Therefore the worst case of accessing, inserting and erasing elements in the list is $\mathcal{O}(\log n)$, which is the height of the tree. For examples and explanations, I have found the following link to be useful: https://www.geeksforgeeks.org/self-balancing-binary-search-trees/
