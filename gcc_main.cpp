#include "clang_lib.h"


// Output:
//
// Clang:
// Reference: 0 0x7ffd4e743cbf
// Lambda: 0 0x7ffd4e743cbf
// GCC:
// Reference: 0 0x7ffd4e743cbf
// Lambda: 1316240575 (nil)
//
// GCC should print the same values in the lambda,
// instead the arguments are reversed.
int main() {
  printf("Clang: \n");
  Test test;
  printf("GCC: \n");
  test.run(0);
}
