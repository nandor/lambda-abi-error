#include "clang_lib.h"

Test::Test() {
  // Pin an implementation of the lambda into this compilation unit.
  // Banning the inlining of Test::sink ensures that.
  run(0);
}

void
__attribute__((noinline))
Test::sink(const std::function<void(void)> &fn) {
  fn();
}

void Test::dostuff(int x) {
  printf("Lambda: %d %p\n", x, this);
}
