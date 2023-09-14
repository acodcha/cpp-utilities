// Copyright 2023 Alexandre Coderre-Chabot
//
// This file is licensed under the MIT license. For more information, visit:
//     https://mit-license.org
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//   - The above copyright notice and this permission notice shall be included
//     in all copies or substantial portions of the Software.
//   - THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
//     OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
//     MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
//     NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
//     DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
//     OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
//     USE OR OTHER DEALINGS IN THE SOFTWARE.
//
// This file was originally obtained from:
//     https://github.com/acodcha/cpp-utilities

#ifndef CPP_UTILITIES_INCLUDE_CONSTEXPR_SQRT_HPP
#define CPP_UTILITIES_INCLUDE_CONSTEXPR_SQRT_HPP

#include <cmath>
#include <limits>

// Namespace that encompasses all of the C++ Utilities library's content.
namespace utility {

// Namespace that contains internal implementation details of the C++ Utilities
// library. Content within this namespace is not meant to be used except by the
// the C++ Utilities library's own functions and classes.
namespace internal {

// Efficient square root solver. This function is a constant expression, unlike
// std::sqrt. This function is an internal implementation detail and is not
// intended to be used except by the utility::constexpr_sqrt function.
inline constexpr double constexpr_sqrt_solver(
    const double number, const double factor) noexcept {
  // Recursively factor the input number until it falls within the [0.25, 4]
  // interval, which greatly reduces the number of Newton-Raphson iterations
  // needed to numerically compute the square root. When solving s = sqrt(x), if
  // x can be expressed as x = n^2 * y such that y is geometrically closer than
  // x to 1, then solving s = n * sqrt(y) requires much fewer Newton-Raphson
  // iterations than solving for s = sqrt(x). The values used as interval
  // endpoints are all powers of 2, which minimize floating-point errors thanks
  // to the IEEE 754 floating-point arithmetic standard. The interval endpoints
  // are:
  //   2^(-16) = 1.52587890625e-5
  //   2^(-8)  = 0.00390625
  //   2^(-4)  = 0.0625
  //   2^(-2)  = 0.25
  //   2^2     = 4
  //   2^4     = 16
  //   2^8     = 256
  //   2^16    = 65536
  //   2^32    = 4294967296
  //   2^64    = 18446744073709551616
  if (number >= 0.25) {
    // Interval: [0.25, +inf[
    if (number <= 4.0) {
      // Interval: [0.25, 4]
      // Use an iterative Newton-Raphson method to numerically compute the
      // square root. Thanks to the factoring done previously, only a few
      // iterations are typically needed.
      double current = number;
      double previous = 0.5 * (current + 1.0);
      while (current != previous) {
        previous = current;
        current = 0.5 * (current + number / current);
      }
      // Finally, re-apply the factor to obtain the square root of the original
      // input number.
      return current * factor;
    } else {
      // Interval: ]4, +inf[
      if (number <= 256.0) {
        // Interval: ]4, 256]
        if (number <= 16.0) {
          // Interval: ]4, 16]
          return constexpr_sqrt_solver(number * 0.25, 2.0 * factor);
        } else {
          // Interval: ]16, 256]
          return constexpr_sqrt_solver(number * 0.0625, 4.0 * factor);
        }
      } else {
        // Interval: ]256, +inf[
        if (number <= 4294967296.0) {
          // Interval: ]256, 4294967296]
          if (number <= 65536.0) {
            // Interval: ]256, 65536]
            return constexpr_sqrt_solver(number * 0.00390625, 16.0 * factor);
          } else {
            // Interval: ]65536, 4294967296]
            return constexpr_sqrt_solver(
                number * 1.52587890625e-5, 256.0 * factor);
          }
        } else {
          // Interval: ]4294967296, +inf[
          if (number <= 18446744073709551616.0) {
            // Interval: ]4294967296, 18446744073709551616]
            return constexpr_sqrt_solver(
                number / 4294967296.0, 65536.0 * factor);
          } else {
            // Interval: ]18446744073709551616, +inf[
            return constexpr_sqrt_solver(
                number / 18446744073709551616.0, 4294967296.0 * factor);
          }
        }
      }
    }
  } else {
    // Interval: ]0, 0.25[
    if (number >= 0.00390625) {
      // Interval: [0.00390625, 0.25[
      if (number >= 0.0625) {
        // Interval: [0.0625, 0.25[
        return constexpr_sqrt_solver(number * 4.0, 0.5 * factor);
      } else {
        // Interval: [0.00390625, 0.0625[
        return constexpr_sqrt_solver(number * 16.0, 0.25 * factor);
      }
    } else {
      // Interval: ]0, 0.00390625[
      if (number >= 0.0000152587890625) {
        // Interval: [1.52587890625e-5, 0.00390625[
        return constexpr_sqrt_solver(number * 256.0, 0.0625 * factor);
      } else {
        // Interval: ]0, 1.52587890625e-5[
        return constexpr_sqrt_solver(number * 65536.0, 0.00390625 * factor);
      }
    }
  }
}

}  // namespace internal

// Returns the square root of a double-precision floating-point number. This
// function is a constant expression, unlike std::sqrt.
inline constexpr double constexpr_sqrt(const double number) noexcept {
  // The square root of zero is zero. Notably, the square root solver does not
  // handle this value, so it must be treated separately.
  if (number == 0.0) {
    return number;
  }

  // The square root of a negative number or of an undefined number is
  // undefined.
  if (number < 0.0 || std::isnan(number)) {
    return std::numeric_limits<double>::quiet_NaN();
  }

  // The square root of positive infinity is positive infinity.
  if (number == std::numeric_limits<double>::infinity()) {
    return number;
  }

  return internal::constexpr_sqrt_solver(number, 1.0);
}

}  // namespace utility

#endif  // CPP_UTILITIES_INCLUDE_CONSTEXPR_SQRT_HPP
