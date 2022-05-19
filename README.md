Lambda ABI mismatch
=====

To run the test:

```
make
./error
```

The test consists of a class exposing a method that can be inlined
(marked as `always_inline` here to ensure consistency), which sets up a lambda
and passes it to a helper function.
Due to the use of a member function call, Clang and GCC order the captured
items differently.
GCC inlines the creation site of the lambda, setting up the closure according
to its own computed capture list, which is then passed to the body of the
lambda compiled by Clang using a different capture list.

Instead of printing the `this` pointer and the value of `x` in the correct
order, arguments are reversed and nonsense is printed.

The linker fails to match lambda methods with their creation sites: both the
Clang and the GCC objects reference their correct versions, however after
linking the two implementations are deduplicated and both point to the one
emitted by Clang.
