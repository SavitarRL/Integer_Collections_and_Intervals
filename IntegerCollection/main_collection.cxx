#include <iostream>
#include <chrono>
#include "tests.cxx"

int main(int, char **) { 

  auto start_time = std::chrono::high_resolution_clock::now();

  // from tests.cxx
  TestCollection();
  
  auto end_time = std::chrono::high_resolution_clock::now();

  auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);

  std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;
  
  return 0;
}