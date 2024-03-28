#include "test.h"
#include "intervals.cxx"
#include <iostream>
#include <limits>
#include <vector>

// checking the implementation of the GetUnionisedIntervals() function
void TestUnion() {
  {
    TEST("Two intervals with no overlap");
    std::vector<Interval> others = {{1, 3}, {5, 7}};
    std::vector<Interval> union_others = GetUnionisedIntervals(others);
    ASSERT_EQ(union_others.size(), 2);
    ASSERT_EQ(union_others[0].Min(), 1);
    ASSERT_EQ(union_others[0].Max(), 3);
    ASSERT_EQ(union_others[1].Min(), 5);
    ASSERT_EQ(union_others[1].Max(), 7);
  }

  {
    TEST("Three intervals with no overlap");
    std::vector<Interval> others = {{2, 4}, {6, 8}, {10, 12}};
    std::vector<Interval> union_others = GetUnionisedIntervals(others);
    ASSERT_EQ(union_others.size(), 3);
    ASSERT_EQ(union_others[0].Min(), 2);
    ASSERT_EQ(union_others[0].Max(), 4);
    ASSERT_EQ(union_others[1].Min(), 6);
    ASSERT_EQ(union_others[1].Max(), 8);
    ASSERT_EQ(union_others[2].Min(), 10);
    ASSERT_EQ(union_others[2].Max(), 12);
  }

  {
    TEST("Two intervals with partial overlap");
    std::vector<Interval> others = {{1, 5}, {3, 7}};
    std::vector<Interval> union_others = GetUnionisedIntervals(others);
    ASSERT_EQ(union_others.size(), 1);
    ASSERT_EQ(union_others[0].Min(), 1);
    ASSERT_EQ(union_others[0].Max(), 7);
  }

  {
    TEST("Three intervals with partial overlap");
    std::vector<Interval> others = {{1, 4}, {3, 6}, {5, 8}};
    std::vector<Interval> union_others = GetUnionisedIntervals(others);
    ASSERT_EQ(union_others.size(), 1);
    ASSERT_EQ(union_others[0].Min(), 1);
    ASSERT_EQ(union_others[0].Max(), 8);
  }

  {
    TEST("Two intervals with complete overlap");
    std::vector<Interval> others = {{1, 5}, {2, 4}};
    std::vector<Interval> union_others = GetUnionisedIntervals(others);
    ASSERT_EQ(union_others.size(), 1);
    ASSERT_EQ(union_others[0].Min(), 1);
    ASSERT_EQ(union_others[0].Max(), 5);
  }

  {
    TEST("Three intervals with complete overlap");
    std::vector<Interval> others = {{1, 4}, {2, 3}, {3, 5}};
    std::vector<Interval> union_others = GetUnionisedIntervals(others);
    ASSERT_EQ(union_others.size(), 1);
    ASSERT_EQ(union_others[0].Min(), 1);
    ASSERT_EQ(union_others[0].Max(), 5);
  }

  {
    TEST("Two adjacent intervals");
    std::vector<Interval> others = {{2, 7}, {8, 10}};
    std::vector<Interval> union_others = GetUnionisedIntervals(others);
    ASSERT_EQ(union_others.size(), 1);
    ASSERT_EQ(union_others[0].Min(), 2);
    ASSERT_EQ(union_others[0].Max(), 10);
  }

  {
    TEST("Single interval");
    std::vector<Interval> others = {{1, 3}};
    std::vector<Interval> union_others = GetUnionisedIntervals(others);
    ASSERT_EQ(union_others.size(), 1);
    ASSERT_EQ(union_others[0].Min(), 1);
    ASSERT_EQ(union_others[0].Max(), 3);
  }

  {
    TEST("Extreme values");
    std::vector<Interval> others = {{-1000000, -999999}, {999999, 1000000}};
    std::vector<Interval> union_others = GetUnionisedIntervals(others);
    ASSERT_EQ(union_others.size(), 2);
    ASSERT_EQ(union_others[0].Min(), -1000000);
    ASSERT_EQ(union_others[0].Max(), -999999);
    ASSERT_EQ(union_others[1].Min(), 999999);
    ASSERT_EQ(union_others[1].Max(), 1000000);
  }

  {
    TEST("Disjointed point intervals");
    std::vector<Interval> others;
    for (int v : {1, 3, 5, 7, 9, 100}) { 
      others.emplace_back( Interval {v, v} );
    }
    std::vector<Interval> union_others = GetUnionisedIntervals(others);

    ASSERT_EQ(union_others.size(), 6);
    ASSERT_EQ(union_others[0].Min(), 1);
    ASSERT_EQ(union_others[0].Max(), 1);
    ASSERT_EQ(union_others[3].Min(), 7);
    ASSERT_EQ(union_others[3].Max(), 7);
  }

  {
    TEST("Adjacent point intervals");
    std::vector<Interval> others;
    for (int v : {1, 2, 3, 4, 5, 6}) { 
      others.emplace_back( Interval {v, v} );
    }
    std::vector<Interval> union_others = GetUnionisedIntervals(others);
    ASSERT_EQ(union_others.size(), 1);
    ASSERT_EQ(union_others[0].Min(), 1);
    ASSERT_EQ(union_others[0].Max(), 6);
  }
}

// checking implementation of the required IsIntervalInUnionOfOthers() function
void TestInterval() {
  {
    TEST("Return false on empty collection");
    Interval interval {-5, 9};
    std::vector<Interval> others;
    ASSERT_EQ(IsIntervalInUnionOfOthers(interval, others), false);
  }

  {
    TEST("Interval larger than single others interval, no overlap");
    Interval interval {5, 7};
    std::vector<Interval> others{ {0, 1} };
    ASSERT_EQ(IsIntervalInUnionOfOthers(interval, others), false);
  }
  
  {
    TEST("Interval smaller than single others interval, no overlap");
    Interval interval {-2000000, -1500000};
    std::vector<Interval> others{ {2000, 3000} };
    ASSERT_EQ(IsIntervalInUnionOfOthers(interval, others), false);
  }

  {
    TEST("Interval is in between two intervals");
    Interval interval{3, 6};
    std::vector<Interval> others{ {0, 2}, {4, 7}};
    ASSERT_EQ(IsIntervalInUnionOfOthers(interval, others), false);
  }

  {
    TEST("Interval endpoints in two intervals");
    Interval interval{2, 4};
    std::vector<Interval> others{ {0, 2}, {4, 7}};
    ASSERT_EQ(IsIntervalInUnionOfOthers(interval, others), false);
  }

  {
    TEST("Interval is in union of itself");
    Interval interval {0, 3};
    std::vector<Interval> others { interval };
    ASSERT_EQ(IsIntervalInUnionOfOthers(interval, others), true);
  }
  
  {
    TEST("Interval is in union of overlapping intervals");
    Interval interval {0, 3};
    std::vector<Interval> others { {-1, 2}, {2, 5} };
    ASSERT_EQ(IsIntervalInUnionOfOthers(interval, others), true);
  }
  
  {
    TEST("Interval is in union of disjoint intervals");
    Interval interval {0, 3};
    std::vector<Interval> others { {-5, -2}, {5, 10}, {0,2}, {2,3} };
    ASSERT_EQ(IsIntervalInUnionOfOthers(interval, others), true);
  }
  
  {
    TEST("Interval is in union of adjacent intervals");
    Interval interval {0, 3};
    std::vector<Interval> others { {-1, 1}, {2, 5} };
    ASSERT_EQ(IsIntervalInUnionOfOthers(interval, others), true);
  }
  
  {
    TEST("Interval is in union of point intervals");
    Interval interval {5, 9};
    std::vector<Interval> others;
    for (int v : {100, 5, -7, 6, 9, 12, 4, 8, 101, 7}) { 
      others.emplace_back( Interval {v, v} );
    }
    ASSERT_EQ(IsIntervalInUnionOfOthers(interval, others), true);
  }
  
  {
    TEST("Interval is in union of overlapping intervals");
    Interval interval {1, 7};
    std::vector<Interval> others { {5, 10}, {0, 6}, {2, 3} };
    ASSERT_EQ(IsIntervalInUnionOfOthers(interval, others), true);
  }

  {
    TEST("Interval is in large redundant union");
    Interval interval1 {5, 9};
    Interval interval2 {999995, 999995};
    Interval interval3 {-999995, -999995};
    Interval interval4 {-300000, 300000};
    std::vector<Interval> others;
    for (int v = -1000000; v < 1000000; ++v ) {
      others.emplace_back( Interval {-1000000 + v, 1000000 + v} );
    }
    RandomizeVectorOrder(others);
    ASSERT_EQ(IsIntervalInUnionOfOthers(interval1, others), true);
    ASSERT_EQ(IsIntervalInUnionOfOthers(interval2, others), true);
    ASSERT_EQ(IsIntervalInUnionOfOthers(interval3, others), true);
    ASSERT_EQ(IsIntervalInUnionOfOthers(interval4, others), true);
  }

  {
    TEST("Interval is in large union");
    Interval interval1 {5, 9};
    Interval interval2 {999995, 999995};
    Interval interval3 {-999995, -999995};
    Interval interval4 {-300000, 300000};
    std::vector<Interval> others;
    for (int v = -1000000; v < 1000000; ++v ) { 
      others.emplace_back( Interval {v, v} );
    }
    RandomizeVectorOrder(others);
    ASSERT_EQ(IsIntervalInUnionOfOthers(interval1, others), true);
    ASSERT_EQ(IsIntervalInUnionOfOthers(interval2, others), true);
    ASSERT_EQ(IsIntervalInUnionOfOthers(interval3, others), true);
    ASSERT_EQ(IsIntervalInUnionOfOthers(interval4, others), true);
  }

  {
    TEST("Interval is wide");
    try {
      Interval interval {std::numeric_limits<Interval::Integer>::min(),
			 std::numeric_limits<Interval::Integer>::max()};
    
      std::vector<Interval> others;
      others.emplace_back(std::numeric_limits<Interval::Integer>::min(), 0);
      others.emplace_back(-1, std::numeric_limits<Interval::Integer>::max());

      ASSERT_EQ(IsIntervalInUnionOfOthers(interval, others), true);
    } catch (...) {
      ASSERT_EQ(false, true);
    }
  }
}
