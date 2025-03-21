#ifndef UNIQUE_PTR_HPP
#define UNIQUE_PTR_HPP

#include "hstl.hpp"
#include <iostream>
#include <utility>

namespace hstd {

template <typename T> Unique_ptr<T>::Unique_ptr(const Unique_ptr &Obj) {
  this->ptr = Obj.ptr;
}

template <typename T>
Unique_ptr<T> &Unique_ptr<T>::operator=(const Unique_ptr &Obj) {
  this->ptr = Obj.ptr;
  return *this;
}

template <typename T> Unique_ptr<T>::Unique_ptr(Unique_ptr &&dObj) {
  this->ptr = dObj.ptr;
  dObj.ptr = nullptr;
}

template <typename T> void Unique_ptr<T>::operator=(Unique_ptr &&dObj) {
  this->ptr = dObj.ptr;
  dObj.ptr = nullptr;
}

template <typename T> T *Unique_ptr<T>::operator->() const {
  return (this)->ptr;
}

template <typename T> T &Unique_ptr<T>::operator*() const {
  return *(this->ptr);
}

template <typename T> Unique_ptr<T>::~Unique_ptr() {
  std::cout << "Destructor Called, ptr deleted \n";
  delete ptr;
}

template <typename T, typename... Args>
Unique_ptr<T> make_unique(Args &&...args) {
  return Unique_ptr<T>(new T(std::forward<Args>(args)...));
};

} // namespace hstd

#endif
