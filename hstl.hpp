#ifndef HSTL_HPP
#define HSTL_HPP

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <ostream>

namespace hstd {

/*

String Class

*/
class String {
private:
  char *m_buffer;
  size_t m_size;

public:
  String() {};
  String(const char *ch);
  String(const String &s);
  String &operator=(const String &s);
  void Print(std::ostream &os) const;
  String(String &&s);
  ~String();
};
std::ostream &operator<<(std::ostream &os, const hstd::String &s);

/*

Unique_PTR class

*/
template <typename T> class Unique_ptr {
private:
  T *ptr = nullptr;

public:
  Unique_ptr() : ptr(nullptr) {};
  Unique_ptr(T *ptr) : ptr(ptr) {};

  Unique_ptr(const Unique_ptr &obj);
  Unique_ptr &operator=(const Unique_ptr &obj);

  Unique_ptr(Unique_ptr &&dObj);
  void operator=(Unique_ptr &&dObj);

  T *operator->() const;
  T &operator*() const;

  ~Unique_ptr();
};
template <typename T, typename... Args>
Unique_ptr<T> make_unique(Args &&...args);

/*

Shared_Pointer Class

*/
template <typename T> class Shared_ptr {
private:
  T *m_ptr = nullptr;
  uint *m_ref = nullptr;

public:
  Shared_ptr() : m_ptr(nullptr), m_ref(new uint(0)) {};
  Shared_ptr(T *ptr) : m_ptr(ptr), m_ref(new uint(1)) {};

  Shared_ptr(const Shared_ptr &obj);
  Shared_ptr &operator=(const Shared_ptr &obj);

  Shared_ptr(Shared_ptr &&obj);
  Shared_ptr &operator=(Shared_ptr &&obj);

  uint get_count() const;
  T *get() const;

  T *operator->() const;
  T &operator*() const;

  ~Shared_ptr();
};
template <typename T, typename... Args>
Shared_ptr<T> make_shared(Args &&...args);

}; // namespace hstd
#endif
