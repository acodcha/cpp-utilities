# Updatable Priority Queue

[![build and test](https://github.com/acodcha/updatable-priority-queue/actions/workflows/build_and_test.yml/badge.svg?branch=main)](https://github.com/acodcha/updatable-priority-queue/actions/workflows/build_and_test.yml)

Simple C++ priority queue that allows updating the priority of its elements. If you wish to use this implementation in your project, copy the [updatable_priority_queue.hpp](include/updatable_priority_queue.hpp) header file to your source code repository and include it in your C++ source code files with `#include "updatable_priority_queue.hpp"`.

To run unit tests, the following packages are required:

- **C++ Compiler:** Any C++ compiler will do, such as GCC or Clang. On Ubuntu, install GCC with `sudo apt install g++` or Clang with `sudo apt install clang`.
- **CMake:** On Ubuntu, install with `sudo apt install cmake`.

Run unit tests with:

```lang-bash
mkdir build
cd build
cmake .. -DBUILD_TESTING=ON
make --jobs=8
make test
```

This builds and runs the unit tests. The GoogleTest library (<https://github.com/google/googletest>) is used for testing. When testing is enabled, the GoogleTest library is downloaded, compiled, and linked with the source code of this library.

This work is maintained by Alexandre Coderre-Chabot (<https://github.com/acodcha>) and licensed under the MIT license. For more details, see the [LICENSE](LICENSE) file or visit <https://mit-license.org>.
