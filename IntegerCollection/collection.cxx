#include <iostream>
#include <map>

// Store a collection of integers
// * On contruction the collection should be empty.
// * The same entry may be stored more than once so that {1, 5, 5, 9} is a collection of 4 entries
class IntegerCollection {
 public:
  // constructor to the IntegerCollection --> empty & size is zero
  IntegerCollection() {}

  // Insert one entry with the value x
  void Insert(int x);

  // Erase one entry with the value x, if one exists
  void Erase(int x);

  // Erase all entries, x, from <= x < to
  void Erase(int from, int to);
  
  // Return the count of all entries, x, from <= x < to
  size_t Count(int from, int to) const;

 private:
  // data structure of a sorted hash map
  // key: the stored integer ; value: number of occurences of that integer 
  std::map<int, size_t> collection;
};


void IntegerCollection::Insert(int x) {
  
  // insert new element of map if constructor is empty or x is not in collection
  if (collection.size() == 0 || collection.find(x) == collection.end()) {
    collection.insert({x,size_t(1)});
  } else if (collection.find(x) != collection.end()) { 
    // increment count of x if x is in collection
    collection[x]++;
  }
}

void IntegerCollection::Erase(int x) {

  auto it = collection.find(x);
  if ( it != collection.end()) {
    
    // If key x exists, decrement its count
    it->second--;

    if (it->second == 0) {
      // If count becomes zero, erase the key-value pair from the collection
      collection.erase(it);
    }
  }
}

void IntegerCollection::Erase(int from, int to) {
  
  // gets the next greatest element of from 
  auto it_from = collection.lower_bound(from);

  // gets the previous greatest element of to
  auto it_to = collection.lower_bound(to);

  // Iterate over the range [from, to) and erase each element if elements exist
  collection.erase(it_from, it_to);
}

size_t IntegerCollection::Count(int from, int to) const {

  if (collection.size() == 0 || from == to) { return 0; }

  // iterator of the next greatest element of int from 
  auto it_from = collection.lower_bound(from);

  // iterator of the previous greatest element of int to
  auto it_to = collection.lower_bound(to);

  // both pointers at beginning, no need count the element
  // as std::map structure is already sorted
  // if iterator it_to points to the first element
  // iterator it_from is guaranteed to point to the first element
  if (it_to == collection.begin()) { return 0; }
  
  // enforcing [from, to) --> we do not count the last element
  // move pointer to left if it is not in the beginning 
  if (it_to != collection.begin()) { it_to--; }
  
  if (it_from == it_to) { 
    return it_from->second;
  } else {
    size_t count = 0;
    for (auto it = it_from; it != std::next(it_to); it++) {
      count += it->second;
    }
    return count;
  }
}