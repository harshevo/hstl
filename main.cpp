#include "hstl.hpp"
#include "shared_ptr.hpp"
#include "vector.hpp"
#include <iostream>

static int totalAlloc = 0;

void *operator new(size_t size) {
  std::cout << "Allocated size : " << size << std::endl;
  totalAlloc += 1;
  return malloc(size);
}

void operator delete(void *ptr) noexcept {
  std::cout << "deleting memory";
  return free(ptr);
}

template <typename T> void PrintVector(hstd::Vector<T> &list) {
  for (size_t i = 0; i < list.size(); i++) {
    std::cout << list[i] << " ";
  }
  std::cout << std::endl;
}

int main() {
  hstd::Shared_ptr<int> s_ptr = hstd::make_shared<int>(1);

  {
    hstd::Shared_ptr<int> s_ptr2 = s_ptr;
  }
}
