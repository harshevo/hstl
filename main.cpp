#include "hstl.hpp"
#include "shared_ptr.hpp"
#include "vector.hpp"
#include <iostream>

static int totalAlloc = 0;

void *operator new(size_t size) {
  totalAlloc += 1;
  return malloc(size);
}

template <typename T> void PrintVector(hstd::Vector<T> &list) {
  for (size_t i = 0; i < list.size(); i++) {
    std::cout << list[i] << " ";
  }
  std::cout << std::endl;
}

int main() {

  // {
  //   hstd::Shared_ptr<int> ptr = hstd::make_shared<int>(1);
  //   std::cout << ptr.get() << "[refcount: ]" << ptr.get_count() << std::endl;
  //   {
  //     hstd::Shared_ptr<int> ptr2 = ptr;
  //     std::cout << ptr2.get() << "[refcount: ]" << ptr2.get_count()
  //               << std::endl;
  //   }
  //
  //   std::cout << "[ref: ] " << ptr.get_count() << std::endl;
  // }

  // hstd::Vector<int> numbers;
  //
  // numbers.PushBack(1);
  // numbers.PushBack(2);
  // numbers.EmplaceBack(3);
  //
  // PrintVector(numbers);
}
