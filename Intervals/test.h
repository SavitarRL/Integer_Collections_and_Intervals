#include <iostream>
#include <random>

class Test {
public:
  Test(const char *_name) : name(_name) {}
  ~Test() {
    std::cout << "TEST " << name << ": "  << (failed ? "FAILED" : "PASSED") << std::endl;
  }

  bool failed = false;
  
private:
  Test(const Test &) = delete;
  Test &operator=(const Test &) = delete;
  const char *name;
};

#define TEST(name) Test test((name))
#define ASSERT_EQ(expr, val)                                        \
  do {                                                              \
    if ((expr) != (val)) {                                          \
      std::cout                                                     \
        << "FAILED: (" << #expr << ") == (" << #val << ") [Got "    \
        << (expr) << " != " << (val) << "]"                         \
        << std::endl;                                               \
      test.failed = true;                                           \
    }                                                               \
  } while(false)

// Modify the elements of the "data" vector to be in a randomised order
template<typename T>
void RandomizeVectorOrder(std::vector<T> &data)
{
  std::default_random_engine generator(0);
  std::uniform_int_distribution<size_t> distribution(0, data.size() - 1);
  for (size_t i = 0; i < data.size(); ++i)
  {
    std::swap(data[distribution(generator)],
	      data[distribution(generator)]);
  }
}

