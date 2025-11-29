#ifndef TESTUTILS_HPP
#define TESTUTILS_HPP

#include <string>
#include <iostream>
#include <cstddef> 

namespace TestUtils {
  class NullBuffer : public std::streambuf {
  public:
    int overflow(int c);
    std::streamsize xsputn(const char* s, std::streamsize n);
  };

  class BufferManager {
  public:
    static std::streambuf* getOriginalStdout();
  };

  class ScopedSilencer {
  private:
    std::streambuf* saved_buf;
    NullBuffer null_buf;
    ScopedSilencer(const ScopedSilencer&);
    ScopedSilencer& operator=(const ScopedSilencer&);

  public:
    ScopedSilencer();
    ~ScopedSilencer();
  };

  class ScopedUnsilencer {
  private:
    std::streambuf* saved_buf;
    ScopedUnsilencer(const ScopedUnsilencer&);
    ScopedUnsilencer& operator=(const ScopedUnsilencer&);

  public:
    ScopedUnsilencer();
    ~ScopedUnsilencer();
  };

  template <typename T>
  void execOrthodoxCanonicalFormFunctions() {
    std::cout << "=== Target Class: " << typeid(T).name() << " ===" << std::endl;
    {
      std::cout << "-- Default constructor --" << std::endl;
      T defaultInstance;
    }
    {
      std::cout << std::endl << "-- Copy constructor --" << std::endl;
      ScopedSilencer silencer;
      T defaultInstance;
      {
        ScopedUnsilencer unsilencer;
        T copyInstance(defaultInstance);
      }
    }
    {
      std::cout << std::endl << "-- Copy assignment operator --" << std::endl;
      ScopedSilencer silencer;
      T defaultInstance;
      T copyInstance;
      {
        ScopedUnsilencer unsilencer;
        copyInstance = defaultInstance;
      }
    }
    std::cout << std::endl;
  }
}

#endif
