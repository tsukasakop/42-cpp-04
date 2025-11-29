#include "TestUtils.hpp"

namespace TestUtils {
  int NullBuffer::overflow(int c) { 
    return c;
  }
  
  std::streamsize NullBuffer::xsputn(const char*, std::streamsize n) { 
    return n; 
  }

  std::streambuf* BufferManager::getOriginalStdout() {
    static std::streambuf* original = std::cout.rdbuf();
    return original;
  }

  ScopedSilencer::ScopedSilencer() {
    BufferManager::getOriginalStdout();
    saved_buf = std::cout.rdbuf();
    std::cout.rdbuf(&null_buf);
  }

  ScopedSilencer::~ScopedSilencer() {
    std::cout.rdbuf(saved_buf);
  }

  ScopedUnsilencer::ScopedUnsilencer() {
    saved_buf = std::cout.rdbuf();
    std::cout.rdbuf(BufferManager::getOriginalStdout());
  }

  ScopedUnsilencer::~ScopedUnsilencer() {
    if (saved_buf != NULL) {
      std::cout.rdbuf(saved_buf);
    }
  }
}
