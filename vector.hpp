#include "hstl.hpp"
#include <iostream>
#include <utility>

using namespace hstd;

template <typename T> void Vector<T>::ReAlloc(size_t new_Capacity) {

  size_t size = m_size;

  if (new_Capacity < size) {
    size = new_Capacity;
  }

  T *newBlock = (T *)::operator new(new_Capacity * sizeof(T));

  for (size_t i = 0; i < size; i++) {
    new (&newBlock[i]) T(m_data[i]);
  }

  for (size_t i = 0; i < size; i++) {
    m_data[i].~T();
  }

  ::operator delete(m_data, m_capacity * sizeof(T));
  m_data = newBlock;
  m_capacity = new_Capacity;
}

template <typename T> T &Vector<T>::PushBack(T &&data) {
  std::cout << "Move" << std::endl;
  if (m_size >= m_capacity) {
    m_capacity = m_capacity + (m_capacity / 2);
    ReAlloc(m_capacity);
  }
  m_data[m_size] = std::move(data);
  return m_data[m_size++];
}

template <typename T> void Vector<T>::PopBack() {
  if (m_size <= (m_capacity / 2)) {
    m_capacity = m_size;
    ReAlloc(m_capacity);
  }

  m_size--;
  m_data[m_size].~T();
}

template <typename T> const T &Vector<T>::operator[](size_t index) const {
  if (index > m_size) {
    std::cout << "Index out of range" << std::endl;
  }
  return m_data[index];
}

template <typename T> T &Vector<T>::operator[](size_t index) {

  if (index > m_size) {
    std::cout << "Index Out of range" << std::endl;
    ;
  }
  return m_data[index];
}

template <typename T>
template <typename... Args>
T &Vector<T>::EmplaceBack(Args &&...args) {
  if (m_size >= m_capacity) {
    size_t new_capacity = m_capacity + m_capacity / 2;
    ReAlloc(new_capacity);
  }

  new (&m_data[m_size]) T(std::forward<Args>(args)...);
  return m_data[m_size++];
}

template <typename T> void Vector<T>::Erase(size_t index) {
  if (index > m_size) {
    std::cout << "Index out of Bounds" << std::endl;
  }

  if (index == m_size) {
    PopBack();
    return;
  }

  for (size_t i = index; i < m_size - 1; i++) {
    m_data[i] = m_data[i + 1];
  }
  m_size--;
}

template <typename T> size_t Vector<T>::size() const { return m_size; }

template <typename T> size_t Vector<T>::capacity() const { return m_capacity; }

template <typename T> void Vector<T>::Clear() {
  for (size_t i = 0; i < m_size; i++) {
    m_data[i].~T();
  }
  m_size = 0;
}

template <typename T> Vector<T>::~Vector() {
  Clear();
  ::operator delete(m_data, m_capacity * sizeof(T));
}
