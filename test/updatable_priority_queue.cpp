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

#include "../include/cpp-utilities/updatable_priority_queue.hpp"

#include <gtest/gtest.h>

namespace utility {

namespace {

TEST(UpdatablePriorityQueue, CopyAssignmentOperator) {
  updatable_priority_queue<std::string, double> first;
  EXPECT_TRUE(first.insert("Alice", 10.0));

  updatable_priority_queue<std::string, double> second;
  EXPECT_TRUE(first.insert("Bob", 20.0));
  second = first;
  EXPECT_EQ(first.size(), second.size());
  EXPECT_EQ(first.front_value(), second.front_value());
  EXPECT_EQ(first.front_priority(), second.front_priority());
}

TEST(UpdatablePriorityQueue, CopyConstructor) {
  updatable_priority_queue<std::string, double> first;
  EXPECT_TRUE(first.insert("Alice", 10.0));

  const updatable_priority_queue<std::string, double> second{first};
  EXPECT_EQ(first.size(), second.size());
  EXPECT_EQ(first.front_value(), second.front_value());
  EXPECT_EQ(first.front_priority(), second.front_priority());
}

TEST(UpdatablePriorityQueue, DefaultConstructor) {
  updatable_priority_queue<std::string, double> queue;
  EXPECT_TRUE(queue.empty());
  EXPECT_EQ(queue.size(), 0);
}

TEST(UpdatablePriorityQueue, Empty) {
  updatable_priority_queue<std::string, double> queue;
  EXPECT_TRUE(queue.empty());

  EXPECT_TRUE(queue.insert("Alice", 10.0));
  EXPECT_FALSE(queue.empty());

  EXPECT_TRUE(queue.erase_front());
  EXPECT_TRUE(queue.empty());
}

TEST(UpdatablePriorityQueue, EraseFront) {
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

TEST(UpdatablePriorityQueue, FrontPriority) {
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

TEST(UpdatablePriorityQueue, FrontValue) {
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

TEST(UpdatablePriorityQueue, Insert) {
  updatable_priority_queue<std::string, double> queue;
  EXPECT_TRUE(queue.insert("Alice", 10.0));
  EXPECT_TRUE(queue.insert("Bob", 20.0));
  EXPECT_TRUE(queue.insert("Claire", 30.0));
  EXPECT_FALSE(queue.insert("Alice", 40.0));
  EXPECT_TRUE(queue.insert("David", 10.0));
  EXPECT_TRUE(queue.insert("Erin", 10.0));
}

TEST(UpdatablePriorityQueue, MoveAssignmentOperator) {
  updatable_priority_queue<std::string, double> reference;
  EXPECT_TRUE(reference.insert("Alice", 10.0));

  updatable_priority_queue<std::string, double> first;
  EXPECT_TRUE(first.insert("Alice", 10.0));

  updatable_priority_queue<std::string, double> second;
  second = std::move(first);
  EXPECT_EQ(second.size(), reference.size());
  EXPECT_EQ(second.front_value(), reference.front_value());
  EXPECT_EQ(second.front_priority(), reference.front_priority());
}

TEST(UpdatablePriorityQueue, MoveConstructor) {
  updatable_priority_queue<std::string, double> reference;
  EXPECT_TRUE(reference.insert("Alice", 10.0));

  updatable_priority_queue<std::string, double> first;
  EXPECT_TRUE(first.insert("Alice", 10.0));

  updatable_priority_queue<std::string, double> second{std::move(first)};
  EXPECT_EQ(second.size(), reference.size());
  EXPECT_EQ(second.front_value(), reference.front_value());
  EXPECT_EQ(second.front_priority(), reference.front_priority());
}

TEST(UpdatablePriorityQueue, NonUniquePriorities) {
  updatable_priority_queue<std::string, double> queue;
  EXPECT_TRUE(queue.insert("Alice", 10.0));
  EXPECT_TRUE(queue.insert("Bob", 20.0));
  EXPECT_TRUE(queue.insert("Claire", 10.0));
  EXPECT_TRUE(queue.insert("David", 10.0));
  EXPECT_EQ(queue.front_value(), "Alice");
  EXPECT_EQ(queue.front_priority(), 10.0);

  EXPECT_TRUE(queue.update("Alice", 20.0));
  EXPECT_EQ(queue.front_value(), "Claire");
  EXPECT_EQ(queue.front_priority(), 10.0);

  EXPECT_TRUE(queue.erase_front());
  EXPECT_EQ(queue.front_value(), "David");
  EXPECT_EQ(queue.front_priority(), 10.0);

  EXPECT_TRUE(queue.erase_front());
  EXPECT_EQ(queue.front_value(), "Alice");
  EXPECT_EQ(queue.front_priority(), 20.0);

  EXPECT_TRUE(queue.erase_front());
  EXPECT_EQ(queue.front_value(), "Bob");
  EXPECT_EQ(queue.front_priority(), 20.0);
}

TEST(UpdatablePriorityQueue, Size) {
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

TEST(UpdatablePriorityQueue, UniqueValues) {
  updatable_priority_queue<std::string, double> queue;
  EXPECT_TRUE(queue.insert("Alice", 10.0));
  EXPECT_TRUE(queue.insert("Bob", 20.0));
  EXPECT_TRUE(queue.insert("Claire", 5.0));
  EXPECT_FALSE(queue.insert("Alice", 10.0));
  EXPECT_FALSE(queue.insert("Alice", 15.0));
}

TEST(UpdatablePriorityQueue, Update) {
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
