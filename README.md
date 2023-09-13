# Updatable Priority Queue

[![build and test](https://github.com/acodcha/updatable-priority-queue/actions/workflows/build_and_test.yml/badge.svg?branch=main)](https://github.com/acodcha/updatable-priority-queue/actions/workflows/build_and_test.yml)

Simple C++ priority queue that allows updating the priority of its elements.

The C++ Standard Template Library's priority queue (`std::priority_queue`) does not support updating the priority of its elements. Certain use cases such as Dijkstra's algorithm require this operation. This project implements a priority queue that supports updating the priority of its elements and achieves the same asymptotic time complexity and asymptotic space complexity as the C++ Standard Template Library's implementation.

If you wish to use this implementation in your project, copy the [updatable_priority_queue.hpp](include/updatable_priority_queue.hpp) header file to your source code repository and include it in your C++ source code files with `#include "updatable_priority_queue.hpp"`.

This project requires the following packages:

- **C++11 Compiler:** Any C++11 compiler will do, such as GCC or Clang. On Ubuntu, install GCC with `sudo apt install g++` or Clang with `sudo apt install clang`.
- **CMake:** On Ubuntu, install CMake with `sudo apt install cmake`.

Clone this project's repository and configure it with:

```bash
git clone git@github.com:acodcha/updatable-priority-queue.git
cd updatable-priority-queue
mkdir build
cd build
cmake ..
```

This is a header-only library, so no compilation is needed.

Testing is optional, disabled by default, and requires the following additional package:

- **GoogleTest**: The GoogleTest library (<https://github.com/google/googletest>) is used for testing. On Ubuntu, install it with `sudo apt install libgtest-dev`. When testing is enabled, if the GoogleTest library is not found on your system, it is automatically downloaded, built, and linked with this project.

You can manually test this project on your system from the `build` directory with:

```bash
cmake .. -DTEST_UPDATABLE_PRIORITY_QUEUE=ON
make --jobs=16
make test
```

This project is maintained by Alexandre Coderre-Chabot (<https://github.com/acodcha>) and licensed under the MIT license. For more details, see the [LICENSE](LICENSE) file or visit <https://mit-license.org>.
