// Copyright 2023 Alexandre Coderre-Chabot
//
// This file is licensed under the MIT license. For more information, visit:
//     https://mit-license.org
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
// associated documentation files (the "Software"), to deal in the Software without restriction,
// including without limitation the rights to use, copy, modify, merge, publish, distribute,
// sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//   - The above copyright notice and this permission notice shall be included in all copies or
//   substantial portions of the Software.
//   - THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
//   BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
//   NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
//   DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
// This file was originally obtained from:
//     https://github.com/acodcha/cpp-utilities

#include "../include/cpp-utilities/constexpr_sqrt.hpp"

#include <gtest/gtest.h>

namespace utility {

namespace {

TEST(ConstexprSqrt, CornerCases) {
  EXPECT_TRUE(std::isnan(constexpr_sqrt(std::numeric_limits<double>::quiet_NaN())));

  EXPECT_TRUE(std::isnan(constexpr_sqrt(-std::numeric_limits<double>::infinity())));

  EXPECT_TRUE(std::isnan(constexpr_sqrt(-2.0)));

  EXPECT_EQ(constexpr_sqrt(0.0), std::sqrt(0.0));

  EXPECT_EQ(constexpr_sqrt(1.0), std::sqrt(1.0));

  EXPECT_EQ(constexpr_sqrt(std::numeric_limits<double>::min()),
            std::sqrt(std::numeric_limits<double>::min()));

  EXPECT_DOUBLE_EQ(constexpr_sqrt(std::numeric_limits<double>::max()),
                   std::sqrt(std::numeric_limits<double>::max()));

  EXPECT_TRUE(std::isinf(constexpr_sqrt(std::numeric_limits<double>::infinity())));
}

TEST(ConstexprSqrt, Numbers) {
  EXPECT_EQ(constexpr_sqrt(1.234567890123456789e-128), std::sqrt(1.234567890123456789e-128));

  EXPECT_EQ(constexpr_sqrt(1.234567890123456789e-64), std::sqrt(1.234567890123456789e-64));

  EXPECT_EQ(constexpr_sqrt(1.234567890123456789e-32), std::sqrt(1.234567890123456789e-32));

  EXPECT_EQ(constexpr_sqrt(1.234567890123456789e-16), std::sqrt(1.234567890123456789e-16));

  EXPECT_EQ(constexpr_sqrt(1.234567890123456789e-8), std::sqrt(1.234567890123456789e-8));

  EXPECT_EQ(constexpr_sqrt(1.234567890123456789e-4), std::sqrt(1.234567890123456789e-4));

  EXPECT_DOUBLE_EQ(constexpr_sqrt(1.234567890123456789e-3), std::sqrt(1.234567890123456789e-3));

  EXPECT_DOUBLE_EQ(constexpr_sqrt(1.234567890123456789e-2), std::sqrt(1.234567890123456789e-2));

  EXPECT_DOUBLE_EQ(constexpr_sqrt(1.234567890123456789e-1), std::sqrt(1.234567890123456789e-1));

  EXPECT_DOUBLE_EQ(constexpr_sqrt(0.1234567890123456789), std::sqrt(0.1234567890123456789));

  EXPECT_DOUBLE_EQ(constexpr_sqrt(1.234567890123456789), std::sqrt(1.234567890123456789));

  EXPECT_DOUBLE_EQ(constexpr_sqrt(12.34567890123456789), std::sqrt(12.34567890123456789));

  EXPECT_DOUBLE_EQ(constexpr_sqrt(123.4567890123456789), std::sqrt(123.4567890123456789));

  EXPECT_DOUBLE_EQ(constexpr_sqrt(1234.567890123456789), std::sqrt(1234.567890123456789));

  EXPECT_DOUBLE_EQ(constexpr_sqrt(1.234567890123456789e4), std::sqrt(1.234567890123456789e4));

  EXPECT_EQ(constexpr_sqrt(1.234567890123456789e8), std::sqrt(1.234567890123456789e8));

  EXPECT_EQ(constexpr_sqrt(1.234567890123456789e16), std::sqrt(1.234567890123456789e16));

  EXPECT_EQ(constexpr_sqrt(1.234567890123456789e32), std::sqrt(1.234567890123456789e32));

  EXPECT_EQ(constexpr_sqrt(1.234567890123456789e64), std::sqrt(1.234567890123456789e64));

  EXPECT_EQ(constexpr_sqrt(1.234567890123456789e128), std::sqrt(1.234567890123456789e128));
}

}  // namespace

}  // namespace utility
