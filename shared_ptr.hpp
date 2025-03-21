#pragma once

#include "hstl.hpp"
#include <iostream>
#include <utility>

namespace hstd {

template <typename T> Shared_ptr<T>::Shared_ptr(const Shared_ptr &obj) {
  this->m_ptr = obj.m_ptr;
  this->m_ref = obj.m_ref;

  if (obj.m_ptr != nullptr) {
    (*this->m_ref)++;
  }
}

template <typename T>
Shared_ptr<T> &Shared_ptr<T>::operator=(const Shared_ptr &obj) {
  this->m_ptr = obj.m_ptr;
  this->m_ref = obj.m_ref;

  if (obj.m_ptr != nullptr) {
    (*this->m_ref)++;
  }
}

template <typename T> Shared_ptr<T>::Shared_ptr(Shared_ptr &&obj) {
  this->m_ptr = obj.m_ptr;
  this->m_ref = obj.m_ref;

  obj.m_ptr = nullptr;
  obj.m_ref = nullptr;
}

template <typename T>
Shared_ptr<T> &Shared_ptr<T>::operator=(Shared_ptr &&obj) {
  this->m_ptr = obj.m_ptr;
  this->m_ref = obj.m_ref;

  obj.m_ptr = nullptr;
  obj.m_ref = nullptr;
  return *this;
}

template <typename T> uint Shared_ptr<T>::get_count() const { return *m_ref; }

template <typename T> T *Shared_ptr<T>::get() const { return m_ptr; }

template <typename T> T *Shared_ptr<T>::operator->() const { return m_ptr; }

template <typename T> T &Shared_ptr<T>::operator*() const { return *m_ptr; }

template <typename T> Shared_ptr<T>::~Shared_ptr() {
  std::cout << "Destructor Called [Ref: ] " << *m_ref << "Deleted\n";
  (*m_ref)--;
  if (*m_ref == 0) {
    if (m_ptr != nullptr) {
      delete m_ptr;
    }
    delete m_ref;
  }
}

template <typename T, typename... Args>
Shared_ptr<T> make_shared(Args &&...args) {
  return Shared_ptr<T>(new T(std::forward<Args>(args)...));
};

} // namespace hstd
