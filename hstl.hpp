#ifndef HSTL_HPP
#define HSTL_HPP

#include <cstddef>
#include <cstring>
#include <ostream>

namespace hstd {

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

};
std::ostream& operator<<(std::ostream& os, const hstd::String& s);
#endif
