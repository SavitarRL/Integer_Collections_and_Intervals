#include <iostream>
#include <limits>
#include "test.h"
#include "collection.cxx"

void TestCollection(){
  {   
    TEST("empty on construction");
    IntegerCollection empty;
    ASSERT_EQ(empty.Count(std::numeric_limits<int>::min(), std::numeric_limits<int>::max()), size_t(0));
  }
  
  {
    TEST("collection contains 5 ones");
    IntegerCollection fiveOnes;
    for (int v : {1, 1, 1, 1, 1}) {
      fiveOnes.Insert(v);
    }
    ASSERT_EQ(fiveOnes.Count(std::numeric_limits<int>::min(), std::numeric_limits<int>::max()), size_t(5));
    ASSERT_EQ(fiveOnes.Count(1,std::numeric_limits<int>::max()), size_t(5));
    ASSERT_EQ(fiveOnes.Count(std::numeric_limits<int>::min(), 2), size_t(5));
    ASSERT_EQ(fiveOnes.Count(1,2), size_t(5));
  }
  
  {
    TEST("collection contains 3 twos");
    IntegerCollection threeTwos;
    for (int v : {-3, 2, 7, 2, 1, 2}) {
      threeTwos.Insert(v);
    }
    ASSERT_EQ(threeTwos.Count(std::numeric_limits<int>::min(), std::numeric_limits<int>::max()), size_t(6));
    ASSERT_EQ(threeTwos.Count(2,3), size_t(3));
  }
  
  {
    TEST("collection contains 2 fives");
    IntegerCollection twoFives;
    for (int v : {5, 2, 5, 5, 3, 2}) {
      twoFives.Insert(v);
    }
    for (int v : {1, 5, 3, 1}) {
      twoFives.Erase(v);
    }
    ASSERT_EQ(twoFives.Count(std::numeric_limits<int>::min(), std::numeric_limits<int>::max()), size_t(4));
    ASSERT_EQ(twoFives.Count(5,6), size_t(2));
  }
  
  {
    TEST("range erase");
    IntegerCollection noTeens;
    for (int v : {-1, 5, 11, 14, 14, 19, 20, 21, 30}) {
      noTeens.Insert(v);
    }
    ASSERT_EQ(noTeens.Count(std::numeric_limits<int>::min(), std::numeric_limits<int>::max()), size_t(9));
    noTeens.Erase(13,20);
    ASSERT_EQ(noTeens.Count(std::numeric_limits<int>::min(), std::numeric_limits<int>::max()), size_t(6));
  }
  
  {
    TEST("range count");
    IntegerCollection bagOfNumbers;
    for (int v : {-1, 5, 11, 14, 14, 19, 20, 21, 30}) {
      bagOfNumbers.Insert(v);
    }
    ASSERT_EQ(bagOfNumbers.Count(std::numeric_limits<int>::min(), std::numeric_limits<int>::max()), size_t(9));
    ASSERT_EQ(bagOfNumbers.Count(-10,-1), size_t(0));
    ASSERT_EQ(bagOfNumbers.Count(-10,0), size_t(1));
    ASSERT_EQ(bagOfNumbers.Count(10,11), size_t(0));
    ASSERT_EQ(bagOfNumbers.Count(11,11), size_t(0));
    ASSERT_EQ(bagOfNumbers.Count(11,12), size_t(1));
    ASSERT_EQ(bagOfNumbers.Count(11,14), size_t(1));
    ASSERT_EQ(bagOfNumbers.Count(11,15), size_t(3));
    ASSERT_EQ(bagOfNumbers.Count(14,15), size_t(2));
    ASSERT_EQ(bagOfNumbers.Count(14,100), size_t(6));
  }

  {
    TEST("Insert/count/erase significant quantity of random data");
    IntegerCollection bagOfNumbers;
    std::vector<int> numbers;
    const size_t size = 500000;
    numbers.reserve(size);
    for (size_t ii = 0 ; ii < size; ++ii) {
      numbers.push_back(ii);
    }
    RandomizeVectorOrder(numbers);
    for (int i : numbers) {
      bagOfNumbers.Insert(i);
    }
    ASSERT_EQ(bagOfNumbers.Count(0, size), size);
    int total = 0;
    for (int i : numbers) {
      total += bagOfNumbers.Count(i, i+1);
    }
    ASSERT_EQ(total, size);
    for (int i : numbers) {
      bagOfNumbers.Erase(i);
    }
    ASSERT_EQ(bagOfNumbers.Count(0, size), size_t(0));
  }

}