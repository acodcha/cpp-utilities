# C++ Utilities

[![build and test](https://github.com/acodcha/cpp-utilities/actions/workflows/build_and_test.yaml/badge.svg?branch=main)](https://github.com/acodcha/cpp-utilities/actions/workflows/build_and_test.yaml)

Various utilities that extend the C++ Standard Library.

- [Contents](#contents)
  - [Constant Expression Square Root](#constant-expression-square-root)
  - [Updatable Priority Queue](#updatable-priority-queue)
- [Configuration](#configuration)
- [Testing](#testing)
- [License](#license)

## Contents

- [Constant Expression Square Root](#constant-expression-square-root)
- [Updatable Priority Queue](#updatable-priority-queue)

[(Back to Top)](#c-utilities)

### Constant Expression Square Root

Constant expression (`constexpr`) square root solver. Note that `std::sqrt` is not a constant expression. Returns the same result as `std::sqrt` to within one unit in the last place.

```C++
constexpr double square_root_of_two = utility::constexpr_sqrt(2.0);
```

If you wish to use this implementation in your project, copy the [constexpr_sqrt.hpp](include/cpp-utilities/constexpr_sqrt.hpp) header file to your source code repository and include it in your C++ source code files with `#include "constexpr_sqrt.hpp"`.

[(Back to Contents)](#contents)

### Updatable Priority Queue

Simple C++ priority queue that allows updating the priority of its elements.

```C++
utility::updatable_priority_queue<std::string, double> name_and_score;

name_and_score.insert("Alice", 10.0);
name_and_score.insert("Bob", 15.0);
name_and_score.insert("Claire", 5.0);
std::cout << name_and_score.head_value() << std::endl;  // Claire

name_and_score.update("Claire", 20.0);
std::cout << name_and_score.head_value() << std::endl;  // Alice

name_and_score.remove_head();
std::cout << name_and_score.head_value() << std::endl;  // Bob
```

The C++ Standard Library's priority queue (`std::priority_queue`) does not support updating the priority of its elements. However, certain use cases such as Dijkstra's algorithm require this operation. This project implements a priority queue that supports updating the priority of its elements and achieves the same asymptotic time complexity and asymptotic space complexity as the C++ Standard Library's implementation.

If you wish to use this implementation in your project, copy the [updatable_priority_queue.hpp](include/cpp-utilities/updatable_priority_queue.hpp) header file to your source code repository and include it in your C++ source code files with `#include "updatable_priority_queue.hpp"`.

[(Back to Contents)](#contents)

## Configuration

This project requires the following packages:

- **C++11 Compiler:** Any C++11 compiler will do, such as GCC or Clang. On Ubuntu, install GCC with `sudo apt install g++` or Clang with `sudo apt install clang`.
- **CMake:** On Ubuntu, install CMake with `sudo apt install cmake`.

Clone this project's repository and configure it with:

```bash
git clone git@github.com:acodcha/cpp-utilities.git
cd cpp-utilities
mkdir build
cd build
cmake ..
```

This is a header-only library, so no compilation is needed.

[(Back to Top)](#c-utilities)

## Testing

Testing is optional, disabled by default, and requires the following additional package:

- **GoogleTest**: The GoogleTest library (<https://github.com/google/googletest>) is used for testing. On Ubuntu, install it with `sudo apt install libgtest-dev`. When testing is enabled, if the GoogleTest library is not found on your system, it is automatically downloaded, built, and linked with this project.

You can manually test this project from the `build` directory with:

```bash
cmake .. -DTEST_CPP_UTILITIES=ON
make --jobs=16
make test
```

[(Back to Top)](#c-utilities)

## License

This project is maintained by Alexandre Coderre-Chabot (<https://github.com/acodcha>) and licensed under the MIT license. For more details, see the [LICENSE](LICENSE) file or visit <https://mit-license.org>.

[(Back to Top)](#c-utilities)
