#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>

// Demonstrates different cache associativity patterns
class CacheAssociativityDemo {
private:
  // Function to measure access time for a specific access pattern
  template <typename AccessPattern>
  long long measureAccessTime(AccessPattern pattern, int iterations) {
    std::vector<int> data(1024 * 1024,
                          0); // Large enough to potentially exceed cache

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < iterations; ++i) {
      pattern(data);
    }

    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
        .count();
  }

public:
  // Demonstrates different cache access patterns
  void demonstrateCacheAssociativity() {
    const int ITERATIONS = 1000;

    // Direct Mapped (Lowest Associativity)
    auto directMappedAccess = [](std::vector<int> &data) {
      int sum = 0;
      // Access elements that map to the same cache line
      for (size_t i = 0; i < data.size();
           i += 64) { // Assuming 64-byte cache lines
        sum += data[i];
      }
      return sum;
    };

    // Fully Associative (Highest Associativity)
    auto fullyAssociativeAccess = [](std::vector<int> &data) {
      int sum = 0;
      // Random-like access pattern
      for (size_t i = 0; i < data.size(); i += 17) {
        sum += data[i];
      }
      return sum;
    };

    // N-Way Set Associative (Middle Ground)
    auto setAssociativeAccess = [](std::vector<int> &data) {
      int sum = 0;
      // Access pattern with some locality
      for (size_t i = 0; i < data.size(); i += 32) {
        sum += data[i];
      }
      return sum;
    };

    // Measure and print access times
    std::cout << "Cache Associativity Performance Comparison\n";
    std::cout << "----------------------------------------\n";
    std::cout << "Direct Mapped Access Time:      " << std::fixed
              << std::setprecision(2)
              << measureAccessTime(directMappedAccess, ITERATIONS) << " ns\n";

    std::cout << "Set Associative Access Time:   " << std::fixed
              << std::setprecision(2)
              << measureAccessTime(setAssociativeAccess, ITERATIONS) << " ns\n";

    std::cout << "Fully Associative Access Time: " << std::fixed
              << std::setprecision(2)
              << measureAccessTime(fullyAssociativeAccess, ITERATIONS)
              << " ns\n";
  }
};

int main() {
  CacheAssociativityDemo demo;
  demo.demonstrateCacheAssociativity();
  return 0;
}
