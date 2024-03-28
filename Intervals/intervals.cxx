#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>
#include <stack>
#include <chrono>

// Represents a closed interval [min, max] 
// Enforces min < max
class Interval { 
 public:
  typedef long int Integer;
  
  Interval (Integer _min, Integer _max) : min(_min), max(_max) {
    if (max < min) {
      std::swap(min, max); 
    }
  }
  Integer Min() const { return min; }
  Integer Max() const { return max; }

  static bool CompareIntervals(const Interval& a, const Interval& b) {
    return a.Min() < b.Min();
  }

 private:
  Integer min;
  Integer max;
};

// Helper function to unionise the collection of intervals A1... An
std::vector<Interval> GetUnionisedIntervals(const std::vector<Interval> &others) { 

  std::vector<Interval> union_others;
  std::stack<Interval> stack;

  // making a copy of others for sorting
  std::vector<Interval> sorted_others = others;

  // Sort the intervals based on the start value. Runtime complexity: O(nlog(n))
  std::sort(sorted_others.begin(), sorted_others.end(), Interval::CompareIntervals);

  Interval current = sorted_others[0];

  // Iterate through sorted intervals and merge overlapping intervals
  for (int i = 1; i < sorted_others.size(); ++i) {
    if (sorted_others[i].Min() <= current.Max() + 1) {
      // Merge the current interval with the next interval
      current = Interval(current.Min(), std::max(current.Max(), sorted_others[i].Max()));
    } else {
      // No overlap, add the current interval to union_others and update current
      union_others.push_back(current);
      current = sorted_others[i];
    }
  }

  // Add the last merged interval to union_others
  union_others.push_back(current);
  return union_others;
}

// utility function for binary search in the unionised, sorted vector of intervals
// returns true if the input interval is in the vector of intervals, returns false otherwise
bool BinarySearchInterval(const std::vector<Interval>& union_others, int interval_min, int interval_max) {
  int left = 0;
  int right = union_others.size() - 1;

  while (left <= right) {
    int mid = left + (right - left) / 2;
    const Interval& current = union_others[mid];

    if (interval_min >= current.Min() && interval_max <= current.Max()) {
      return true; // Interval is within the current merged interval
    } else if (interval_max < current.Min()) {
      right = mid - 1; // search left
    } else {
      left = mid + 1; // search right
    }
  }
  return false; // Interval not found
}

// Return true if and only if every element of test is contained in the union of others
bool IsIntervalInUnionOfOthers(const Interval &interval, const std::vector<Interval> &others) {
  
  // catching empty interval or empty collection
  if (others.size() == 0) { return false; } 

  Interval::Integer interval_min = interval.Min();
  Interval::Integer interval_max = interval.Max();

  // compare directly when there is a single continuous interval
  if (others.size() == 1) { 
    Interval::Integer others_min = others[0].Min();
    Interval::Integer others_max = others[0].Max();
    return interval_min >= others_min && interval_max <= others_max;
  }
  
  // get a sorted, unionised vector of intervals 
  std::vector<Interval> union_others = GetUnionisedIntervals(others);

  // compare directly when there is a single continuous interval after sorting
  if (union_others.size() == 1) { 
    Interval::Integer union_others_min = union_others[0].Min();
    Interval::Integer union_others_max = union_others[0].Max();
    return interval_min >= union_others_min && interval_max <= union_others_max;
  }
  
  // if the intervals are not continuous, check where the interval lies
  // implementing binary search to check if the input interval is in the vector of intervals
  return BinarySearchInterval(union_others, interval_min,  interval_max);
}