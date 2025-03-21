#include "hstl.hpp"
#include "shared_ptr.hpp"
#include <iostream>

int main() {

  {
    hstd::Shared_ptr<int> ptr = hstd::make_shared<int>(1);
    std::cout << ptr.get() << "[refcount: ]" << ptr.get_count() << std::endl;
    {
      hstd::Shared_ptr<int> ptr2 = ptr;
      std::cout << ptr2.get() << "[refcount: ]" << ptr2.get_count()
                << std::endl;
    }

    std::cout << "[ref: ] " << ptr.get_count() << std::endl;
  }
}
