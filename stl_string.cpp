#include "hstl.hpp"
#include <cstdio>
#include <cstring>
#include <iostream>
#include <ostream>

// constructor
hstd::String::String(const char *ch) {
  m_size = strlen(ch);
  m_buffer = new char[m_size + 1];
  strcpy(m_buffer, ch);
}

// copy assignement
hstd::String &hstd::String::operator=(const hstd::String &s) {
  m_size = s.m_size;
  m_buffer = new char[m_size + 1];
  strcpy(m_buffer, s.m_buffer);
  return *this;
}

// move constructor
hstd::String::String(hstd::String &&s) {
  m_size = s.m_size;
  m_buffer = s.m_buffer;
  s.m_buffer = nullptr;
}

hstd::String::String(const hstd::String &s) {
  m_size = s.m_size;
  m_buffer = new char[m_size + 1];
  strcpy(m_buffer, s.m_buffer);
}

void hstd::String::Print(std::ostream &os) const { os << m_buffer; }

std::ostream &operator<<(std::ostream &os, const hstd::String &s) {
  s.Print(os);
  return os;
}

hstd::String::~String() {
  std::cout << "Destructor Called \n";
  delete[] m_buffer;
}
