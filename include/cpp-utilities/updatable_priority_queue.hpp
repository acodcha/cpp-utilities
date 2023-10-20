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
#include <set>

// Namespace that encompasses all of the C++ Utilities library's content.
namespace utility {

// Simple C++ priority queue where the priorities of elements can be updated.
// Each element consist of a value and a priority; multiple values can have the
// same priority, but values must be unique.
//
// By default, elements in the queue are ordered by increasing priority given by
// std::less<Priority> such that the element with the lowest priority is at the
// front of the queue. This can be changed by providing a different
// PriorityComparator.
//
// If multiple elements in the queue have the same priority, by default they are
// ordered by increasing value given by std::less<Value> such that the lowest
// value appears first. This can be changed by providing a different
// ValueComparator.
template <class Value, class Priority,
          class PriorityComparator = std::less<Priority>,
          class ValueComparator = std::less<Value>>
class updatable_priority_queue {
public:
  // Default constructor. Constructs an empty queue.
  updatable_priority_queue() = default;

  // Destructor. Destroys this queue.
  ~updatable_priority_queue() noexcept = default;

  // Copy constructor. Constructs a queue by copying another one.
  constexpr updatable_priority_queue(
      const updatable_priority_queue& other) = default;

  // Move constructor. Constructs a queue by moving another one.
  constexpr updatable_priority_queue(
      updatable_priority_queue&& other) noexcept = default;

  // Copy assignment operator. Assigns this queue by copying another one.
  constexpr updatable_priority_queue& operator=(
      const updatable_priority_queue& other) = default;

  // Move assignment operator. Assigns this queue by moving another one.
  constexpr updatable_priority_queue& operator=(
      updatable_priority_queue&& other) noexcept = default;

  // Returns whether this queue is empty. The time complexity is O(1).
  bool empty() const noexcept {
    return value_to_priority_.empty();
  }

  // Returns the number of elements in this queue. The time complexity is O(1).
  std::size_t size() const noexcept {
    return value_to_priority_.size();
  }

  // Returns the value of the front element in this queue. If multiple elements
  // are tied for the front priority, returns the first element value given by
  // ValueComparator. Results in undefined behavior if this queue is empty, so
  // make sure the queue is not empty before calling this function. The time
  // complexity is O(1).
  const Value& front_value() const noexcept {
    return *priority_to_values_.begin()->second.begin();
  }

  // Returns the priority of the front element in this queue. Results in
  // undefined behavior if this queue is empty, so make sure this queue is not
  // empty before calling this function. The time complexity is O(1).
  const Priority& front_priority() const noexcept {
    return priority_to_values_.begin()->first;
  }

  // Attempts to erase the front element in this queue. Returns true if the
  // front element is successfully erased, or false if this queue is empty. The
  // time complexity is O(log(N)), where N is the number of elements in this
  // queue.
  bool erase_front() {
    // If this queue is empty, there is nothing to erase.
    if (empty()) {
      return false;
    }

    // Erase the value that corresponds to the first priority from the map of
    // values to priorities.
    value_to_priority_.erase(*priority_to_values_.begin()->second.begin());

    // Erase the first value of the first priority from the map of priorities to
    // values.
    priority_to_values_.begin()->second.erase(
        priority_to_values_.begin()->second.begin());

    // If the first priority no longer has any associated values, erase it.
    if (priority_to_values_.begin()->second.empty()) {
      priority_to_values_.erase(priority_to_values_.begin());
    }

    return true;
  }

  // Attempts to insert a new element into this queue. Returns true if the new
  // element is inserted, or false if the given value is already in this queue.
  // The time complexity is O(log(N)), where N is the number of elements in this
  // queue.
  bool insert(const Value& value, const Priority& priority) {
    // Check whether the given value is already in this queue.
    if (value_to_priority_.find(value) != value_to_priority_.cend()) {
      // In this case, the given value is already in this queue, and values must
      // be unique, so the given value cannot be inserted.
      return false;
    }

    // In this case, the given value is not already in this queue, so it can be
    // inserted.

    // Insert the given value and the given priority in the map of values to
    // priorities.
    value_to_priority_.emplace(value, priority);

    // Check if the given priority already exists in this queue.
    const typename std::map<Priority, std::set<Value, ValueComparator>,
                            PriorityComparator>::iterator
        found_priority_and_values = priority_to_values_.find(priority);

    if (found_priority_and_values == priority_to_values_.end()) {
      // In this case, the given priority is not already in this queue, so
      // insert it in the map of priorities to values.
      priority_to_values_.emplace(
          priority, std::set<Value, ValueComparator>{value});
    } else {
      // In this case, the given priority is already in this queue, so update
      // its set of associated values.
      found_priority_and_values->second.emplace(value);
    }

    // Return that the insertion was successful.
    return true;
  }

  // Attempts to update the priority of an element in this queue. Returns true
  // if the element with the given value is successfully updated to the new
  // priority, or false if the given value does not corresponds to an element in
  // this queue. The time complexity is O(log(N)), where N is the number of
  // elements in this queue.
  bool update(const Value& value, const Priority& priority) {
    // Check whether the given value is in this queue.
    const typename std::map<Value, Priority, ValueComparator>::iterator
        found_value_and_priority = value_to_priority_.find(value);

    if (found_value_and_priority == value_to_priority_.end()) {
      // In this case, the given value is not in this queue, so its priority
      // cannot be updated.
      return false;
    }

    // In this case, the given value is in this queue, so its priority can be
    // updated.

    // Obtain the old priority of the given value. This is guaranteed to exist
    // in the map of priorities to values.
    const typename std::map<Priority, std::set<Value, ValueComparator>,
                            PriorityComparator>::iterator
        old_priority_and_values =
            priority_to_values_.find(found_value_and_priority->second);

    // Remove the value from the old priority.
    old_priority_and_values->second.erase(value);
    if (old_priority_and_values->second.empty()) {
      priority_to_values_.erase(old_priority_and_values);
    }

    // Check if the new priority already exists in this queue.
    const typename std::map<Priority, std::set<Value, ValueComparator>,
                            PriorityComparator>::iterator
        new_priority_and_values = priority_to_values_.find(priority);

    if (new_priority_and_values == priority_to_values_.end()) {
      // In this case, the new priority does not already exist in this queue, so
      // insert it.
      priority_to_values_.emplace(
          priority, std::set<Value, ValueComparator>{value});
    } else {
      // In this case, the new priority already exists in this queue, so add the
      // updated value to it.
      new_priority_and_values->second.emplace(value);
    }

    // Update the old priority to the new priority in the map of values to
    // priorities.
    found_value_and_priority->second = priority;

    // Return that the update was successful.
    return true;
  }

private:
  // Map of values to their corresponding priorities. Values are unique. This is
  // an auxiliary data structure used to lookup the priority of a given value.
  std::map<Value, Priority, ValueComparator> value_to_priority_;

  // Map of priorities to values. This is the actual queue. Priorities are not
  // unique; there can be multiple values associated with the same priority.
  std::map<Priority, std::set<Value, ValueComparator>, PriorityComparator>
      priority_to_values_;
};

}  // namespace utility

#endif  // CPP_UTILITIES_INCLUDE_UPDATABLE_PRIORITY_QUEUE_HPP
