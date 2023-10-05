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

#ifndef CPP_UTILITIES_INCLUDE_UPDATABLE_PRIORITY_QUEUE_HPP
#define CPP_UTILITIES_INCLUDE_UPDATABLE_PRIORITY_QUEUE_HPP

#include <map>

// Namespace that encompasses all of the C++ Utilities library's content.
namespace utility {

// Simple priority queue that allows updating the priority of its elements.
// Furthermore, multiple elements can have the same priority, though this is
// less efficient and somewhat defeats the purpose of using a priority queue.
//
// By default, elements in the queue are ordered in increasing order of priority
// given by std::less<Priority>, such that the element with the lowest priority
// is at the front of the queue. This can be changed by providing a different
// PriorityComparator.
//
// If multiple elements in the queue have the same priority, by default they are
// ordered in increasing value given by std::less<Value>. This can be changed by
// providing a different ValueComparator.
template <class Value, class Priority,
          class PriorityComparator = std::less<Priority>,
          class ValueComparator = std::less<Value>>
class updatable_priority_queue {
public:
  // Constructs an empty queue.
  updatable_priority_queue() = default;

  // Returns whether the queue is empty. The time complexity is O(1).
  bool empty() const noexcept {
    return value_to_priority_.empty();
  }

  // Returns the number of elements in the queue. The time complexity is O(1).
  std::size_t size() const noexcept {
    return value_to_priority_.size();
  }

  // Returns the value of the front element in the queue. If multiple elements
  // are tied for the front priority, returns the first element value given by
  // ValueComparator. Results in undefined behavior if the queue is empty, so
  // make sure the queue is not empty before calling this function. The time
  // complexity is O(1).
  const Value& front_value() const noexcept {
    return priority_to_values_.begin()->second;
  }

  // Returns the priority of the front element in the queue. Results in
  // undefined behavior if the queue is empty, so make sure the queue is not
  // empty before calling this function. The time complexity is O(1).
  const Priority& front_priority() const noexcept {
    return priority_to_values_.begin()->first;
  }

  // Attempts to erase the front element in the queue. Returns true if the front
  // element is successfully erased, or false if the queue is empty. The time
  // complexity is O(log(N)), where N is the number of elements in the queue.
  bool erase_front() {
    if (empty()) {
      return false;
    }
    value_to_priority_.erase(priority_to_values_.begin()->second);
    priority_to_values_.erase(priority_to_values_.begin());
    return true;
  }

  // Attempts to insert a new element into the queue. Returns true if the new
  // element is inserted, or false if the element is already in the queue. The
  // time complexity is O(log(N)), where N is the number of elements in the
  // queue.
  bool insert(const Value& value, const Priority& priority) {
    if (value_to_priority_.find(value) != value_to_priority_.cend()) {
      return false;
    }
    value_to_priority_.emplace(value, priority);
    priority_to_values_.emplace(priority, value);
    return true;
  }

  // Attempts to update the priority of an element in the queue. Returns true if
  // the element with the given value is successfully updated to the new
  // priority, or false if the given value is not in the queue. The time
  // complexity is O(log(N)), where N is the number of elements in the queue.
  bool update(const Value& value, const Priority& priority) {
    const typename std::map<Value, Priority, ValueComparator>::iterator
        found_value_and_priority = value_to_priority_.find(value);

    if (found_value_and_priority == value_to_priority_.end()) {
      return false;
    }

    const std::pair<
        typename std::multimap<Priority, Value, PriorityComparator>::iterator,
        typename std::multimap<Priority, Value, PriorityComparator>::iterator>
        found_priority_and_values =
            priority_to_values_.equal_range(found_value_and_priority->second);

    for (typename std::multimap<Priority, Value, PriorityComparator>::iterator
             priority_and_value = found_priority_and_values.first;
         priority_and_value != found_priority_and_values.second;
         ++priority_and_value) {
      if (priority_and_value->second == value) {
        priority_to_values_.erase(priority_and_value);
        break;
      }
    }

    found_value_and_priority->second = priority;

    priority_to_values_.emplace(priority, value);

    return true;
  }

private:
  // Map of values to their corresponding priorities.
  std::map<Value, Priority, ValueComparator> value_to_priority_;

  // Map of priorities to values. There can be multiple values for the same
  // priority, so this is a multimap.
  std::multimap<Priority, Value, PriorityComparator> priority_to_values_;
};

}  // namespace utility

#endif  // CPP_UTILITIES_INCLUDE_UPDATABLE_PRIORITY_QUEUE_HPP
