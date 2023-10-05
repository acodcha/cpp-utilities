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

#include "../include/cpp-utilities/updatable_priority_queue.hpp"

#include <gtest/gtest.h>

namespace utility {

namespace {

TEST(updatable_priority_queue, empty) {
  updatable_priority_queue<std::string, double> queue;
  EXPECT_TRUE(queue.empty());
  EXPECT_TRUE(queue.insert("Alice", 10.0));
  EXPECT_FALSE(queue.empty());
  EXPECT_TRUE(queue.erase_front());
  EXPECT_TRUE(queue.empty());
}

TEST(updatable_priority_queue, erase_front) {
  updatable_priority_queue<std::string, double> queue;
  EXPECT_FALSE(queue.erase_front());
  EXPECT_TRUE(queue.insert("Alice", 10.0));
  EXPECT_TRUE(queue.insert("Bob", 20.0));
  EXPECT_TRUE(queue.insert("Claire", 30.0));
  EXPECT_TRUE(queue.erase_front());
  EXPECT_TRUE(queue.erase_front());
  EXPECT_TRUE(queue.erase_front());
  EXPECT_FALSE(queue.erase_front());
}

TEST(updatable_priority_queue, front_priority) {
  updatable_priority_queue<std::string, double> queue;
  EXPECT_TRUE(queue.insert("Alice", 10.0));
  EXPECT_EQ(queue.front_priority(), 10.0);
  EXPECT_TRUE(queue.insert("Bob", 20.0));
  EXPECT_EQ(queue.front_priority(), 10.0);
  EXPECT_TRUE(queue.insert("Claire", 5.0));
  EXPECT_EQ(queue.front_priority(), 5.0);
  EXPECT_TRUE(queue.erase_front());
  EXPECT_EQ(queue.front_priority(), 10.0);
  EXPECT_TRUE(queue.erase_front());
  EXPECT_EQ(queue.front_priority(), 20.0);
}

TEST(updatable_priority_queue, front_value) {
  updatable_priority_queue<std::string, double> queue;
  EXPECT_TRUE(queue.insert("Alice", 10.0));
  EXPECT_EQ(queue.front_value(), "Alice");
  EXPECT_TRUE(queue.insert("Bob", 20.0));
  EXPECT_EQ(queue.front_value(), "Alice");
  EXPECT_TRUE(queue.insert("Claire", 5.0));
  EXPECT_EQ(queue.front_value(), "Claire");
  EXPECT_TRUE(queue.erase_front());
  EXPECT_EQ(queue.front_value(), "Alice");
  EXPECT_TRUE(queue.erase_front());
  EXPECT_EQ(queue.front_value(), "Bob");
}

TEST(updatable_priority_queue, insert) {
  updatable_priority_queue<std::string, double> queue;
  EXPECT_TRUE(queue.insert("Alice", 10.0));
  EXPECT_TRUE(queue.insert("Bob", 20.0));
  EXPECT_TRUE(queue.insert("Claire", 30.0));
  EXPECT_FALSE(queue.insert("Alice", 40.0));
  EXPECT_TRUE(queue.insert("David", 10.0));
  EXPECT_TRUE(queue.insert("Erin", 10.0));
}

TEST(updatable_priority_queue, size) {
  updatable_priority_queue<std::string, double> queue;
  EXPECT_EQ(queue.size(), 0);
  EXPECT_TRUE(queue.insert("Alice", 10.0));
  EXPECT_EQ(queue.size(), 1);
  EXPECT_TRUE(queue.insert("Bob", 20.0));
  EXPECT_EQ(queue.size(), 2);
  EXPECT_TRUE(queue.erase_front());
  EXPECT_EQ(queue.size(), 1);
  EXPECT_TRUE(queue.erase_front());
  EXPECT_EQ(queue.size(), 0);
}

TEST(updatable_priority_queue, update) {
  updatable_priority_queue<std::string, double> queue;
  EXPECT_TRUE(queue.insert("Alice", 10.0));
  EXPECT_TRUE(queue.insert("Bob", 20.0));
  EXPECT_TRUE(queue.insert("Claire", 5.0));
  EXPECT_EQ(queue.front_value(), "Claire");
  EXPECT_TRUE(queue.update("Claire", 30.0));
  EXPECT_EQ(queue.front_value(), "Alice");
  EXPECT_TRUE(queue.update("Bob", 5.0));
  EXPECT_EQ(queue.front_value(), "Bob");
  EXPECT_FALSE(queue.update("Erin", 40.0));
  EXPECT_TRUE(queue.erase_front());
  EXPECT_EQ(queue.front_value(), "Alice");
  EXPECT_TRUE(queue.erase_front());
  EXPECT_EQ(queue.front_value(), "Claire");
}

}  // namespace

}  // namespace utility
