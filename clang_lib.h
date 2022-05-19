#pragma once

#include <cstdio>
#include <functional>

class Test {
public:
  Test();

  void
  __attribute__((always_inline))
  run(int x) {
    printf("Reference: %d %p\n", x, this);
    // GCC capture order: [x, this]
    // Clang capture order: [this, x]
    //
    // When identifying the captures of a member function call,
    // Clang seems to be placing the this pointer before any
    // arguments, whereas GCC does the exact opposite.
    sink([=] { dostuff(x); });
  }

  void sink(const std::function<void(void)> &fn);

  void dostuff(int r);
};
